#include "m_pd.h"

static t_class* seamless_tilde_class;

typedef struct _seamless {
  	t_object x_obj;
	t_float signal_inlet_dummy;
	t_float seamsize_ratio;
	t_float loopstart_pending;
	t_float loopend_pending;
	t_float loopstart_current;
	t_float loopend_current;
	t_float prev_frame;
	t_float seamsize;
	t_int loop_mode;
	t_int playback_direction;
	t_outlet* outlet_index_0;
	t_outlet* outlet_ratio_0;
	t_outlet* outlet_index_1;
	t_outlet* outlet_ratio_1;
	t_inlet* inlet_playback_direction;
	t_inlet* inlet_seamsize_ratio;
	t_inlet* inlet_loopstart_pending;
	t_inlet* inlet_loopend_pending;
} t_seamless_tilde;


static const t_int LOOP_MODE_NONE = 0;
static const t_int LOOP_MODE_FORWARD = 1;
static const t_int LOOP_MODE_BACKWARD = 2;
static const t_int LOOP_MODE_PINGPONG = 3;

static const t_int PLAYBACK_DIRECTION_FORWARD = 0;
static const t_int PLAYBACK_DIRECTION_BACKWARD = 1;

void seamless_tilde_free(t_seamless_tilde* x){
	inlet_free(x->inlet_playback_direction);
	inlet_free(x->inlet_seamsize_ratio);
	inlet_free(x->inlet_loopstart_pending);
	inlet_free(x->inlet_loopend_pending);
	outlet_free(x->outlet_index_0);
	outlet_free(x->outlet_ratio_0);
	outlet_free(x->outlet_index_1);
	outlet_free(x->outlet_ratio_1);
}

void *seamless_tilde_new(){
	t_seamless_tilde* x = (t_seamless_tilde*)pd_new(seamless_tilde_class);
	x->prev_frame = -1;
	x->inlet_playback_direction = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_signal, &s_signal);
	x->inlet_seamsize_ratio = floatinlet_new(&x->x_obj, &x->seamsize_ratio);
	x->inlet_loopstart_pending = floatinlet_new(&x->x_obj, &x->loopstart_pending);
	x->inlet_loopend_pending = floatinlet_new(&x->x_obj, &x->loopend_pending);
    x->outlet_index_0 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_ratio_0 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_index_1 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_ratio_1 = outlet_new(&x->x_obj, &s_signal);
	return (void*)x;
}

void seamless_tilde_check_playback_direction(t_seamless_tilde* x, t_int new_direction){
	if(new_direction != x->playback_direction){
		post("new direction: %d", new_direction);
		x->playback_direction = new_direction;
		x->seamsize = (t_int)((x->loopend_pending - x->loopstart_pending) * x->seamsize_ratio);
		x->loopstart_current = x->loopstart_pending;
		x->loopend_current = x->loopend_pending;
	}
}

void seamless_none(t_int* w){
	t_sample* in = (t_sample*)(w[2]);
	t_sample* out_index_0 = (t_sample*)(w[3]);
	t_sample* out_ratio_0 = (t_sample*)(w[4]);
	t_sample* out_index_1 = (t_sample*)(w[5]);
	t_sample* out_ratio_1 = (t_sample*)(w[6]);
	int n = (int)(w[7]);
	while (n--){
		*out_index_0++ = *in++;
		*out_ratio_0++ = 1;
		*out_index_1++ = 0;
		*out_ratio_1++ = 0;
	}
}

void seamless_forward(t_int* w){
	t_seamless_tilde* x = (t_seamless_tilde*)(w[1]);
	t_sample* in = (t_sample*)(w[2]);
	t_sample* out_index_0 = (t_sample *)(w[3]);
	t_sample* out_ratio_0 = (t_sample *)(w[4]);
	t_sample* out_index_1 = (t_sample *)(w[5]);
	t_sample* out_ratio_1 = (t_sample *)(w[6]);
	int n = (int)(w[7]);

	while (n--){
		t_float frame1 = *in++;
		if(frame1 > x->loopstart_current + x->seamsize || x->seamsize <= 0){
			*out_index_0++ = frame1;
			*out_ratio_0++ = 1;
			*out_index_1++ = 0;
			*out_ratio_1++ = 0;
		}
		else {
			t_float loop_position = frame1 - x->loopstart_current;
			t_float frame2 = x->loopend_current - x->seamsize + loop_position;
			t_float ratio = loop_position/x->seamsize;
			*out_index_0++ = frame1;
			*out_index_1++ = frame2;
			*out_ratio_0++ = ratio;
			*out_ratio_1++ = 1 - ratio;
		}
		x->prev_frame = frame1;

	}
}

void seamless_pingpong(t_int* w){
	t_seamless_tilde* x = (t_seamless_tilde*)(w[1]);
	t_sample* in_position = (t_sample*)(w[2]);
	t_sample* in_direction = (t_sample*)(w[3]);
	t_sample* out_index_0 = (t_sample *)(w[4]);
	t_sample* out_ratio_0 = (t_sample *)(w[5]);
	t_sample* out_index_1 = (t_sample *)(w[6]);
	t_sample* out_ratio_1 = (t_sample *)(w[7]);
	int n = (int)(w[8]);

	while (n--){
		const t_float frame1 = *in_position++;
		seamless_tilde_check_playback_direction(x, (t_int)*in_direction++);

		if((frame1 < x->loopend_current - x->seamsize && frame1 > x->loopstart_current + x->seamsize) || x->seamsize <= 0){
			*out_index_0++ = frame1;
			*out_ratio_0++ = 1;
			*out_index_1++ = 0;
			*out_ratio_1++ = 0;
			continue;
		}

		if(x->playback_direction == PLAYBACK_DIRECTION_FORWARD){
			if(frame1 >= x->loopend_current - x->seamsize){
				const t_float loop_position = frame1 - x->loopend_current + x->seamsize;
				const t_float ratio = loop_position/x->seamsize;
				const t_float frame2 = x->loopend_current - loop_position;
				post("frame1a: %f loop_position: %f x->seamsize: %f ratio: %f frame2: %f", frame1, loop_position, x->seamsize, ratio, frame2);
				*out_index_0++ = frame1;
				*out_index_1++ = frame2;
				*out_ratio_0++ = 1 - ratio;
				*out_ratio_1++ = ratio;
				continue;
			}
			else {
				const t_float loop_position = frame1;
				const t_float ratio = loop_position/x->seamsize;
				const t_float frame2 = x->seamsize - frame1;
				post("frame1b: %f loop_position: %f x->seamsize: %f ratio: %f frame2: %f", frame1, loop_position, x->seamsize, ratio, frame2);
				*out_index_0++ = frame1;
				*out_index_1++ = frame2;
				*out_ratio_0++ = ratio;
				*out_ratio_1++ = 1 - ratio;
				continue;
			}
		}
		if(x->playback_direction == PLAYBACK_DIRECTION_BACKWARD){
			if(frame1 >= x->loopend_current - x->seamsize){
				const t_float seam_center = x->loopend_current - x->seamsize/2;
				const t_float loop_position = seam_center - frame1 + x->seamsize/2;
				const t_float frame2 = seam_center + (seam_center - frame1);
				const t_float ratio = loop_position/x->seamsize;
				post("frame1c: %f loop_position: %f x->seamsize: %f ratio: %f frame2: %f", frame1, loop_position, x->seamsize, ratio, frame2);
				*out_index_0++ = frame1;
				*out_index_1++ = frame2;
				*out_ratio_0++ = ratio;
				*out_ratio_1++ = 1 - ratio;
				continue;
			}
			else {
				const t_float loop_position = x->seamsize - frame1;
				const t_float ratio = loop_position/x->seamsize;
				const t_float frame2 = x->seamsize - frame1;
				post("frame1d: %f loop_position: %f x->seamsize: %f ratio: %f frame2: %f", frame1, loop_position, x->seamsize, ratio, frame2);
				*out_index_0++ = frame1;
				*out_index_1++ = frame2;
				*out_ratio_0++ = 1 - ratio;
				*out_ratio_1++ = ratio;
				continue;
			}
		}
		
	}

}

t_int *seamless_tilde_perform(t_int* w){
	t_seamless_tilde* x = (t_seamless_tilde*)(w[1]);

	if(x->loop_mode == LOOP_MODE_NONE){
		//seamless_none(w);
		seamless_pingpong(w);
	}
	if(x->loop_mode == LOOP_MODE_FORWARD){
		//seamless_forward(w);
		seamless_pingpong(w);
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
}

void seamless_tilde_noteon(t_seamless_tilde *x, t_floatarg argument){
	x->playback_direction = PLAYBACK_DIRECTION_FORWARD;
	x->seamsize = 0;
	x->loopstart_current = x->loopstart_pending;
	x->loopend_current = x->loopend_pending;
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

}