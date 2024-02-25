#include "m_pd.h"

static t_class* loopoverlap_tilde_class;

static const t_int LOOP_MODE_NONE = 0;
static const t_int LOOP_MODE_FORWARD = 1;
static const t_int LOOP_MODE_BACKWARD = 2;
static const t_int LOOP_MODE_PINGPONG = 3;

static const t_int PLAYBACK_DIRECTION_FORWARD = 0;
static const t_int PLAYBACK_DIRECTION_BACKWARD = 1;

static enum Phase {PreLoopStart, InStartOverlap, OutsideOverlap, InEndOverlap, PostLoopEnd};

typedef struct {
	t_float frame1;
	t_float frame2;
	t_float frame1_ratio;
	t_float frame2_ratio;
} seam_values_struct;

typedef struct _loopoverlap {
  	t_object x_obj;
	t_float signal_inlet_dummy;
	t_float loopstart;
	t_float loopend;
	t_float overlap_ratio;
	t_float overlap_size;
	t_int loop_mode;
	t_outlet* outlet_index_0;
	t_outlet* outlet_ratio_0;
	t_outlet* outlet_index_1;
	t_outlet* outlet_ratio_1;
	t_inlet* inlet_playback_direction;
	t_inlet* inlet_loopstart;
	t_inlet* inlet_loopend;
	t_inlet* inlet_overlap_ratio;
	enum Phase phase;
	t_int play_overlapped;
	seam_values_struct seam_values;
	t_int backward_pingpong;
} t_loopoverlap_tilde;

void loopoverlap_tilde_determine_phase_forward(t_loopoverlap_tilde* x, t_float frame);
void loopoverlap_tilde_determine_phase_backward(t_loopoverlap_tilde* x, t_float frame);
void loopoverlap_tilde_determine_phase_pingpong(t_loopoverlap_tilde* x, t_float frame);
void loopoverlap_tilde_do_pingpong(t_loopoverlap_tilde* x, const t_float frame1, const t_int playback_direction);
void loopoverlap_tilde_determine_play_overlapped(t_loopoverlap_tilde* x);
void loopoverlap_tilde_update_overlap_size(t_loopoverlap_tilde* x);

void loopoverlap_tilde_free(t_loopoverlap_tilde* x){
	inlet_free(x->inlet_playback_direction);
	inlet_free(x->inlet_overlap_ratio);
	inlet_free(x->inlet_loopstart);
	inlet_free(x->inlet_loopend);
	outlet_free(x->outlet_index_0);
	outlet_free(x->outlet_ratio_0);
	outlet_free(x->outlet_index_1);
	outlet_free(x->outlet_ratio_1);
}

void *loopoverlap_tilde_new(){
	t_loopoverlap_tilde* x = (t_loopoverlap_tilde*)pd_new(loopoverlap_tilde_class);
	x->inlet_playback_direction = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
	x->inlet_overlap_ratio = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("overlap_ratio"));
	x->inlet_loopstart = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("loopstart"));
	x->inlet_loopend = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("loopend"));
    x->outlet_index_0 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_ratio_0 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_index_1 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_ratio_1 = outlet_new(&x->x_obj, &s_signal);
	return (void*)x;
}

void loopoverlap_none(t_int* w){
	t_sample* in = (t_sample*)(w[2]);
	t_sample* out_index_0 = (t_sample*)(w[4]);
	t_sample* out_ratio_0 = (t_sample*)(w[5]);
	t_sample* out_index_1 = (t_sample*)(w[6]);
	t_sample* out_ratio_1 = (t_sample*)(w[7]);
	int n = (int)(w[8]);
	while (n--){
		*out_index_0++ = *in++;
		*out_ratio_0++ = 1;
		*out_index_1++ = 0;
		*out_ratio_1++ = 0;
	}
}

void loopoverlap_forward(t_int* w){
	t_loopoverlap_tilde* x = (t_loopoverlap_tilde*)(w[1]);
	t_sample* in_position = (t_sample*)(w[2]);
	t_sample* out_index_0 = (t_sample*)(w[4]);
	t_sample* out_ratio_0 = (t_sample*)(w[5]);
	t_sample* out_index_1 = (t_sample*)(w[6]);
	t_sample* out_ratio_1 = (t_sample*)(w[7]);
	int n = (int)(w[8]);

	while (n--){
		const t_float frame1 = *(in_position++);
		loopoverlap_tilde_determine_phase_forward(x, frame1);
		loopoverlap_tilde_determine_play_overlapped(x);
		if(x->phase != InStartOverlap || !x->play_overlapped){
			*out_index_0++ = frame1;
			*out_ratio_0++ = 1;
			*out_index_1++ = 0;
			*out_ratio_1++ = 0;
		}
		else {
			t_float loop_position = frame1 - x->loopstart;
			t_float frame2 = x->loopend - x->overlap_size + loop_position;
			t_float ratio = loop_position/x->overlap_size;
			*out_index_0++ = frame1;
			*out_index_1++ = frame2;
			*out_ratio_0++ = ratio;
			*out_ratio_1++ = 1 - ratio;
		}
	}
}

void loopoverlap_backward(t_int* w){
	t_loopoverlap_tilde* x = (t_loopoverlap_tilde*)(w[1]);
	t_sample* in_position = (t_sample*)(w[2]);
	t_sample* in_direction = (t_sample*)(w[3]);
	t_sample* out_index_0 = (t_sample*)(w[4]);
	t_sample* out_ratio_0 = (t_sample*)(w[5]);
	t_sample* out_index_1 = (t_sample*)(w[6]);
	t_sample* out_ratio_1 = (t_sample*)(w[7]);
	int n = (int)(w[8]);

	while (n--){
		const t_float frame1 = *(in_position++);
		const t_int playback_direction = (t_int)*in_direction++;

		if(playback_direction == PLAYBACK_DIRECTION_FORWARD){
			loopoverlap_tilde_determine_phase_pingpong(x, frame1);
			loopoverlap_tilde_determine_play_overlapped(x);
			loopoverlap_tilde_do_pingpong(x, frame1, playback_direction);
			x->backward_pingpong = 1;
		}
		else {
			if(!x->backward_pingpong){
				loopoverlap_tilde_determine_phase_backward(x, frame1);
				loopoverlap_tilde_determine_play_overlapped(x);
				if(x->phase != InEndOverlap || !x->play_overlapped){
					x->seam_values.frame1 = frame1;
					x->seam_values.frame1_ratio = 1;
					x->seam_values.frame2 = 0;
					x->seam_values.frame2_ratio = 0;
				}
				else {
					t_float loop_position = x->loopend - frame1;
					t_float ratio = loop_position/x->overlap_size;
					x->seam_values.frame1= frame1;
					x->seam_values.frame2 = x->loopstart + x->overlap_size - loop_position;
					x->seam_values.frame1_ratio = ratio;
					x->seam_values.frame2_ratio = 1 - ratio;
				}
			}
			else {
				loopoverlap_tilde_determine_phase_pingpong(x, frame1);
				loopoverlap_tilde_determine_play_overlapped(x);
				loopoverlap_tilde_do_pingpong(x, frame1, playback_direction);
				x->backward_pingpong = frame1 > x->loopend - x->overlap_size;
			}
		}

		*out_index_0++ = x->seam_values.frame1;
		*out_ratio_0++ = x->seam_values.frame1_ratio;
		*out_index_1++ = x->seam_values.frame2;
		*out_ratio_1++ = x->seam_values.frame2_ratio;
	}
}

void loopoverlap_pingpong(t_int* w){
	t_loopoverlap_tilde* x = (t_loopoverlap_tilde*)(w[1]);
	t_sample* in_position = (t_sample*)(w[2]);
	t_sample* in_direction = (t_sample*)(w[3]);
	t_sample* out_index_0 = (t_sample*)(w[4]);
	t_sample* out_ratio_0 = (t_sample*)(w[5]);
	t_sample* out_index_1 = (t_sample*)(w[6]);
	t_sample* out_ratio_1 = (t_sample*)(w[7]);
	int n = (int)(w[8]);

	while (n--){
		const t_float frame1 = *(in_position++);
		const t_int playback_direction = (t_int)*in_direction++;
		loopoverlap_tilde_determine_phase_pingpong(x, frame1);
		loopoverlap_tilde_determine_play_overlapped(x);	
		loopoverlap_tilde_do_pingpong(x, frame1, playback_direction);
		*out_index_0++ = x->seam_values.frame1;
		*out_index_1++ = x->seam_values.frame2;
		*out_ratio_0++ = x->seam_values.frame1_ratio;
		*out_ratio_1++ = x->seam_values.frame2_ratio;
	}
}

void loopoverlap_tilde_do_pingpong(t_loopoverlap_tilde* x, const t_float frame1, const t_int playback_direction){
	
	x->seam_values.frame1 = frame1;
	
	if((x->phase != InStartOverlap && x->phase != InEndOverlap) || !x->play_overlapped){
		x->seam_values.frame1 = frame1;
		x->seam_values.frame1_ratio = 1;
		x->seam_values.frame2 = 0;
		x->seam_values.frame2_ratio = 0;
		return;
	}

	if(playback_direction == PLAYBACK_DIRECTION_FORWARD){
		if(frame1 >= x->loopend - x->overlap_size){
			const t_float loop_position = frame1 - x->loopend + x->overlap_size;
			x->seam_values.frame2_ratio = loop_position/x->overlap_size;
			x->seam_values.frame1_ratio = 1 - x->seam_values.frame2_ratio;
			x->seam_values.frame2 = x->loopend - loop_position;
		}
		else {
			const t_float loop_position = frame1 - x->loopstart;
			x->seam_values.frame1_ratio = loop_position/x->overlap_size;
			x->seam_values.frame2_ratio = 1 - x->seam_values.frame1_ratio;
			x->seam_values.frame2 = x->loopstart + x->overlap_size - frame1 + x->loopstart;
		}
	}
	else {
		if(frame1 >= x->loopend - x->overlap_size){
			const t_float seam_center = x->loopend - x->overlap_size/2;
			const t_float loop_position = seam_center - frame1 + x->overlap_size/2;
			x->seam_values.frame2 = seam_center + (seam_center - frame1);
			x->seam_values.frame1_ratio = loop_position/x->overlap_size;
			x->seam_values.frame2_ratio = 1 - x->seam_values.frame1_ratio;
		}
		else {
			x->seam_values.frame2 = x->loopstart + x->overlap_size - frame1 + x->loopstart;
			const t_float loop_position = x->seam_values.frame2 - x->loopstart;
			x->seam_values.frame2_ratio = loop_position/x->overlap_size;
			x->seam_values.frame1_ratio = 1 - x->seam_values.frame2_ratio;
		}
	}
}

void loopoverlap_tilde_determine_phase_backward(t_loopoverlap_tilde* x, t_float frame){
	if(frame >= x->loopend - x->overlap_size && frame <= x->loopend){
		x->phase = InEndOverlap;
	}
	if(frame < x->loopend - x->overlap_size){
		x->phase = OutsideOverlap;
	}
	if(frame > x->loopend){
		x->phase = PostLoopEnd;
	}
}

void loopoverlap_tilde_determine_phase_forward(t_loopoverlap_tilde* x, t_float frame){
	if(frame < x->loopstart){
		x->phase = PreLoopStart;
	}
	if(frame >= x->loopstart && frame <= x->loopstart + x->overlap_size){
		x->phase = InStartOverlap;
	}
	if(frame > x->loopstart + x->overlap_size){
		x->phase = OutsideOverlap;
	}
}

void loopoverlap_tilde_determine_phase_pingpong(t_loopoverlap_tilde* x, t_float frame){
	if(frame < x->loopstart){
		x->phase = PreLoopStart;
	}
	if(frame >= x->loopstart && frame <= x->loopstart + x->overlap_size){
		x->phase = InStartOverlap;
	}
	if(frame > x->loopstart + x->overlap_size && frame < x->loopend - x->overlap_size){
		x->phase = OutsideOverlap;
	}
	if(frame >= x->loopend - x->overlap_size && frame <= x->loopend){
		x->phase = InEndOverlap;
	}
	if(frame > x->loopend){
		x->phase = PostLoopEnd;
	}
}

void loopoverlap_tilde_determine_play_overlapped(t_loopoverlap_tilde* x){
	if(x->phase != OutsideOverlap) return;
	x->play_overlapped = 1;
}

t_int *loopoverlap_tilde_perform(t_int* w){
	t_loopoverlap_tilde* x = (t_loopoverlap_tilde*)(w[1]);

	if(x->loop_mode == LOOP_MODE_NONE){
		loopoverlap_none(w);
	}
	if(x->loop_mode == LOOP_MODE_FORWARD){
		loopoverlap_forward(w);
	}
	if(x->loop_mode == LOOP_MODE_BACKWARD){
		loopoverlap_backward(w);
	}
	if(x->loop_mode == LOOP_MODE_PINGPONG){
		loopoverlap_pingpong(w);
	}

	return (w+9);
}

void loopoverlap_tilde_dsp(t_loopoverlap_tilde* x, t_signal** sp){
  	dsp_add(loopoverlap_tilde_perform, 8, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[0]->s_n);
}

void loopoverlap_tilde_loop_mode(t_loopoverlap_tilde *x, t_floatarg argument){
	x->loop_mode = (t_int)argument;
	loopoverlap_tilde_update_overlap_size(x);
}

void loopoverlap_tilde_noteon(t_loopoverlap_tilde *x, t_floatarg argument){
	loopoverlap_tilde_update_overlap_size(x);
	x->play_overlapped = 0;
}

void loopoverlap_tilde_update_overlap_size(t_loopoverlap_tilde* x){
	x->overlap_size = (t_int)((x->loopend - x->loopstart) * x->overlap_ratio);
}

void loopoverlap_tilde_overlap_ratio(t_loopoverlap_tilde* x, t_floatarg overlap_ratio){
	x->overlap_ratio = overlap_ratio;
	loopoverlap_tilde_update_overlap_size(x);
	x->play_overlapped = 0;
}

void loopoverlap_tilde_loopstart(t_loopoverlap_tilde* x, t_floatarg loopstart){
	x->loopstart = (t_int)loopstart;
	loopoverlap_tilde_update_overlap_size(x);
	x->play_overlapped = 0;
}

void loopoverlap_tilde_loopend(t_loopoverlap_tilde* x, t_floatarg loopend){
	x->loopend = (t_int)loopend;
	loopoverlap_tilde_update_overlap_size(x);
	x->play_overlapped = 0;
}

void loopoverlap_tilde_setup(void){
	loopoverlap_tilde_class = class_new(
		gensym("loopoverlap~"),
		(t_newmethod)loopoverlap_tilde_new,
		(t_method)loopoverlap_tilde_free, 
		sizeof(t_loopoverlap_tilde),
		CLASS_DEFAULT, 
        0,
		0
	);

	class_addmethod(loopoverlap_tilde_class, (t_method)loopoverlap_tilde_dsp, gensym("dsp"), A_CANT, 0);

	CLASS_MAINSIGNALIN(loopoverlap_tilde_class, t_loopoverlap_tilde, signal_inlet_dummy);

	class_addmethod(
		loopoverlap_tilde_class, 
		(t_method)loopoverlap_tilde_loop_mode, 
		gensym("loopmode"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		loopoverlap_tilde_class, 
		(t_method)loopoverlap_tilde_noteon, 
		gensym("noteon"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		loopoverlap_tilde_class,
		(t_method)loopoverlap_tilde_overlap_ratio, 
		gensym("overlap_ratio"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		loopoverlap_tilde_class,
		(t_method)loopoverlap_tilde_loopstart, 
		gensym("loopstart"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		loopoverlap_tilde_class,
		(t_method)loopoverlap_tilde_loopend, 
		gensym("loopend"),
		A_DEFFLOAT,
		0
	);

}