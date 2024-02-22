#include "m_pd.h"

static t_class* seamless_tilde_class;

static const t_int LOOP_MODE_NONE = 0;
static const t_int LOOP_MODE_FORWARD = 1;
static const t_int LOOP_MODE_BACKWARD = 2;
static const t_int LOOP_MODE_PINGPONG = 3;

static const t_int PLAYBACK_DIRECTION_FORWARD = 0;
static const t_int PLAYBACK_DIRECTION_BACKWARD = 1;

static enum Phase {PreLoopStart, InStartSeam, OutsideSeam, InEndSeam, PostLoopEnd};

typedef struct {
	t_float frame1;
	t_float frame2;
	t_float frame1_ratio;
	t_float frame2_ratio;
} seam_values_struct;

typedef struct _seamless {
  	t_object x_obj;
	t_float signal_inlet_dummy;
	t_float loopstart;
	t_float loopend;
	t_float seamsize_ratio;
	t_float seamsize;
	t_int loop_mode;
	t_outlet* outlet_index_0;
	t_outlet* outlet_ratio_0;
	t_outlet* outlet_index_1;
	t_outlet* outlet_ratio_1;
	t_inlet* inlet_playback_direction;
	t_inlet* inlet_loopstart;
	t_inlet* inlet_loopend;
	t_inlet* inlet_seamsize_ratio;
	enum Phase phase;
	t_int play_seam;
	seam_values_struct seam_values;
	t_int backward_pingpong;
} t_seamless_tilde;

void seamless_tilde_determine_phase_forward(t_seamless_tilde* x, t_float frame);
void seamless_tilde_determine_phase_backward(t_seamless_tilde* x, t_float frame);
void seamless_tilde_determine_phase_pingpong(t_seamless_tilde* x, t_float frame);
void seamless_tilde_do_pingpong(t_seamless_tilde* x, const t_float frame1, const t_int playback_direction);
void seamless_tilde_determine_play_seam(t_seamless_tilde* x);
void seamless_tilde_update_seamsize(t_seamless_tilde* x);

void seamless_tilde_free(t_seamless_tilde* x){
	inlet_free(x->inlet_playback_direction);
	inlet_free(x->inlet_seamsize_ratio);
	inlet_free(x->inlet_loopstart);
	inlet_free(x->inlet_loopend);
	outlet_free(x->outlet_index_0);
	outlet_free(x->outlet_ratio_0);
	outlet_free(x->outlet_index_1);
	outlet_free(x->outlet_ratio_1);
}

void *seamless_tilde_new(){
	t_seamless_tilde* x = (t_seamless_tilde*)pd_new(seamless_tilde_class);
	x->inlet_playback_direction = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
	x->inlet_seamsize_ratio = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("seamsize_ratio"));
	x->inlet_loopstart = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("loopstart"));
	x->inlet_loopend = inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("loopend"));
    x->outlet_index_0 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_ratio_0 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_index_1 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_ratio_1 = outlet_new(&x->x_obj, &s_signal);
	return (void*)x;
}

void seamless_none(t_int* w){
	t_sample* in = (t_sample*)(w[2]);
	t_sample* out_index_0 = (t_sample*)(w[3]);
	t_sample* out_ratio_0 = (t_sample*)(w[4]);
	t_sample* out_index_1 = (t_sample*)(w[5]);
	t_sample* out_ratio_1 = (t_sample*)(w[6]);
	int n = (int)(w[8]);
	while (n--){
		*out_index_0++ = *in++;
		*out_ratio_0++ = 1;
		*out_index_1++ = 0;
		*out_ratio_1++ = 0;
	}
}

void seamless_forward(t_int* w){
	t_seamless_tilde* x = (t_seamless_tilde*)(w[1]);
	t_sample* in_position = (t_sample*)(w[2]);
	t_sample* out_index_0 = (t_sample*)(w[4]);
	t_sample* out_ratio_0 = (t_sample*)(w[5]);
	t_sample* out_index_1 = (t_sample*)(w[6]);
	t_sample* out_ratio_1 = (t_sample*)(w[7]);
	int n = (int)(w[8]);

	while (n--){
		const t_float frame1 = *(in_position++);
		seamless_tilde_determine_phase_forward(x, frame1);
		seamless_tilde_determine_play_seam(x);
		if(x->phase != InStartSeam || !x->play_seam){
			*out_index_0++ = frame1;
			*out_ratio_0++ = 1;
			*out_index_1++ = 0;
			*out_ratio_1++ = 0;
		}
		else {
			t_float loop_position = frame1 - x->loopstart;
			t_float frame2 = x->loopend - x->seamsize + loop_position;
			t_float ratio = loop_position/x->seamsize;
			*out_index_0++ = frame1;
			*out_index_1++ = frame2;
			*out_ratio_0++ = ratio;
			*out_ratio_1++ = 1 - ratio;
		}
	}
}

void seamless_backward(t_int* w){
	t_seamless_tilde* x = (t_seamless_tilde*)(w[1]);
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
			seamless_tilde_determine_phase_pingpong(x, frame1);
			seamless_tilde_determine_play_seam(x);
			seamless_tilde_do_pingpong(x, frame1, playback_direction);
			x->backward_pingpong = 1;
		}
		else {
			if(!x->backward_pingpong){
				seamless_tilde_determine_phase_backward(x, frame1);
				seamless_tilde_determine_play_seam(x);
				if(x->phase != InEndSeam || !x->play_seam){
					x->seam_values.frame1 = frame1;
					x->seam_values.frame1_ratio = 1;
					x->seam_values.frame2 = 0;
					x->seam_values.frame2_ratio = 0;
				}
				else {
					t_float loop_position = x->loopend - frame1;
					t_float ratio = loop_position/x->seamsize;
					x->seam_values.frame1= frame1;
					x->seam_values.frame2 = x->loopstart + x->seamsize - loop_position;
					x->seam_values.frame1_ratio = ratio;
					x->seam_values.frame2_ratio = 1 - ratio;
				}
			}
			else {
				seamless_tilde_determine_phase_pingpong(x, frame1);
				seamless_tilde_determine_play_seam(x);
				seamless_tilde_do_pingpong(x, frame1, playback_direction);
				x->backward_pingpong = frame1 > x->loopend - x->seamsize;
			}
		}

		*out_index_0++ = x->seam_values.frame1;
		*out_ratio_0++ = x->seam_values.frame1_ratio;
		*out_index_1++ = x->seam_values.frame2;
		*out_ratio_1++ = x->seam_values.frame2_ratio;
	}
}

void seamless_pingpong(t_int* w){
	t_seamless_tilde* x = (t_seamless_tilde*)(w[1]);
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
		seamless_tilde_determine_phase_pingpong(x, frame1);
		seamless_tilde_determine_play_seam(x);	
		seamless_tilde_do_pingpong(x, frame1, playback_direction);
		*out_index_0++ = x->seam_values.frame1;
		*out_index_1++ = x->seam_values.frame2;
		*out_ratio_0++ = x->seam_values.frame1_ratio;
		*out_ratio_1++ = x->seam_values.frame2_ratio;
	}
}

void seamless_tilde_do_pingpong(t_seamless_tilde* x, const t_float frame1, const t_int playback_direction){
	
	x->seam_values.frame1 = frame1;
	
	if((x->phase != InStartSeam && x->phase != InEndSeam) || !x->play_seam){
		x->seam_values.frame1 = frame1;
		x->seam_values.frame1_ratio = 1;
		x->seam_values.frame2 = 0;
		x->seam_values.frame2_ratio = 0;
		return;
	}

	if(playback_direction == PLAYBACK_DIRECTION_FORWARD){
		if(frame1 >= x->loopend - x->seamsize){
			const t_float loop_position = frame1 - x->loopend + x->seamsize;
			x->seam_values.frame2_ratio = loop_position/x->seamsize;
			x->seam_values.frame1_ratio = 1 - x->seam_values.frame2_ratio;
			x->seam_values.frame2 = x->loopend - loop_position;
		}
		else {
			const t_float loop_position = frame1 - x->loopstart;
			x->seam_values.frame1_ratio = loop_position/x->seamsize;
			x->seam_values.frame2_ratio = 1 - x->seam_values.frame1_ratio;
			x->seam_values.frame2 = x->loopstart + x->seamsize - frame1 + x->loopstart;
		}
	}
	else {
		if(frame1 >= x->loopend - x->seamsize){
			const t_float seam_center = x->loopend - x->seamsize/2;
			const t_float loop_position = seam_center - frame1 + x->seamsize/2;
			x->seam_values.frame2 = seam_center + (seam_center - frame1);
			x->seam_values.frame1_ratio = loop_position/x->seamsize;
			x->seam_values.frame2_ratio = 1 - x->seam_values.frame1_ratio;
		}
		else {
			x->seam_values.frame2 = x->loopstart + x->seamsize - frame1 + x->loopstart;
			const t_float loop_position = x->seam_values.frame2 - x->loopstart;
			x->seam_values.frame2_ratio = loop_position/x->seamsize;
			x->seam_values.frame1_ratio = 1 - x->seam_values.frame2_ratio;
		}
	}
}

void seamless_tilde_determine_phase_backward(t_seamless_tilde* x, t_float frame){
	if(frame >= x->loopend - x->seamsize && frame <= x->loopend){
		x->phase = InEndSeam;
	}
	if(frame < x->loopend - x->seamsize){
		x->phase = OutsideSeam;
	}
	if(frame > x->loopend){
		x->phase = PostLoopEnd;
	}
}

void seamless_tilde_determine_phase_forward(t_seamless_tilde* x, t_float frame){
	if(frame < x->loopstart){
		x->phase = PreLoopStart;
	}
	if(frame >= x->loopstart && frame <= x->loopstart + x->seamsize){
		x->phase = InStartSeam;
	}
	if(frame > x->loopstart + x->seamsize){
		x->phase = OutsideSeam;
	}
}

void seamless_tilde_determine_phase_pingpong(t_seamless_tilde* x, t_float frame){
	if(frame < x->loopstart){
		x->phase = PreLoopStart;
	}
	if(frame >= x->loopstart && frame <= x->loopstart + x->seamsize){
		x->phase = InStartSeam;
	}
	if(frame > x->loopstart + x->seamsize && frame < x->loopend - x->seamsize){
		x->phase = OutsideSeam;
	}
	if(frame >= x->loopend - x->seamsize && frame <= x->loopend){
		x->phase = InEndSeam;
	}
	if(frame > x->loopend){
		x->phase = PostLoopEnd;
	}
}

void seamless_tilde_determine_play_seam(t_seamless_tilde* x){
	if(x->phase != OutsideSeam) return;
	x->play_seam = 1;
}

t_int *seamless_tilde_perform(t_int* w){
	t_seamless_tilde* x = (t_seamless_tilde*)(w[1]);

	if(x->loop_mode == LOOP_MODE_NONE){
		seamless_none(w);
	}
	if(x->loop_mode == LOOP_MODE_FORWARD){
		seamless_forward(w);
	}
	if(x->loop_mode == LOOP_MODE_BACKWARD){
		seamless_backward(w);
	}
	if(x->loop_mode == LOOP_MODE_PINGPONG){
		seamless_pingpong(w);
	}

	return (w+9);
}

void seamless_tilde_dsp(t_seamless_tilde* x, t_signal** sp){
  	dsp_add(seamless_tilde_perform, 8, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[4]->s_vec, sp[5]->s_vec, sp[0]->s_n);
}

void seamless_tilde_loop_mode(t_seamless_tilde *x, t_floatarg argument){
	x->loop_mode = (t_int)argument;
	seamless_tilde_update_seamsize(x);
}

void seamless_tilde_noteon(t_seamless_tilde *x, t_floatarg argument){
	seamless_tilde_update_seamsize(x);
	x->play_seam = 0;
}

void seamless_tilde_update_seamsize(t_seamless_tilde* x){
	x->seamsize = (t_int)((x->loopend - x->loopstart) * x->seamsize_ratio);
}

void seamless_tilde_seamsize_ratio(t_seamless_tilde* x, t_floatarg seamsize_ratio){
	x->seamsize_ratio = seamsize_ratio;
	seamless_tilde_update_seamsize(x);
	x->play_seam = 0;
}

void seamless_tilde_loopstart(t_seamless_tilde* x, t_floatarg loopstart){
	x->loopstart = (t_int)loopstart;
	seamless_tilde_update_seamsize(x);
	x->play_seam = 0;
}

void seamless_tilde_loopend(t_seamless_tilde* x, t_floatarg loopend){
	x->loopend = (t_int)loopend;
	seamless_tilde_update_seamsize(x);
	x->play_seam = 0;
}

void seamless_tilde_setup(void){
	seamless_tilde_class = class_new(
		gensym("seamless~"),
		(t_newmethod)seamless_tilde_new,
		(t_method)seamless_tilde_free, 
		sizeof(t_seamless_tilde),
		CLASS_DEFAULT, 
        0,
		0
	);

	class_addmethod(seamless_tilde_class, (t_method)seamless_tilde_dsp, gensym("dsp"), A_CANT, 0);

	CLASS_MAINSIGNALIN(seamless_tilde_class, t_seamless_tilde, signal_inlet_dummy);

	class_addmethod(
		seamless_tilde_class, 
		(t_method)seamless_tilde_loop_mode, 
		gensym("loopmode"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		seamless_tilde_class, 
		(t_method)seamless_tilde_noteon, 
		gensym("noteon"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		seamless_tilde_class,
		(t_method)seamless_tilde_seamsize_ratio, 
		gensym("seamsize_ratio"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		seamless_tilde_class,
		(t_method)seamless_tilde_loopstart, 
		gensym("loopstart"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		seamless_tilde_class,
		(t_method)seamless_tilde_loopend, 
		gensym("loopend"),
		A_DEFFLOAT,
		0
	);

}