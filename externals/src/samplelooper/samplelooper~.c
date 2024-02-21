#include <math.h>
#include "m_pd.h"

static t_class *samplelooper_tilde_class;

typedef struct _samplelooper {
  	t_object x_obj;
	t_float samplestart;
	t_float sampleend;
	t_float loopstart;
	t_float loopend;
	t_float seamsize_ratio;
	t_float position;
	t_float pitch_ratio;
	t_int lfo_enabled;
	t_int loop_mode;
	t_float output_playback_frames;
	int output_playback_frames_counter;
	t_float playback_frames_start;
	t_float playback_frames_end;
	t_int note_stopped;
	t_float processed_seconds;
	t_int playback_direction;
	t_outlet *index_out;
	t_outlet *playback_frames_out;
	t_outlet *playback_direction_out;
	t_outlet *finished_out;
	t_inlet *samplestart_in;
	t_inlet *sampleend_in;
	t_inlet *loopstart_in;
	t_inlet *loopend_in;
	t_inlet *seamsize_ratio_in;
} t_samplelooper_tilde;

static t_float pdsr;
static const int output_playback_frames_every = 5;

static const t_int LOOP_MODE_NONE = 0;
static const t_int LOOP_MODE_FORWARD = 1;
static const t_int LOOP_MODE_BACKWARD = 2;
static const t_int LOOP_MODE_PINGPONG = 3;

static const t_int PLAYBACK_DIRECTION_FORWARD = 0;
static const t_int PLAYBACK_DIRECTION_BACKWARD = 1;

void samplelooper_tilde_noteon_bang(t_samplelooper_tilde *x){
	post("samplelooper_tilde_noteon_bang");
	x->processed_seconds = 0;
	x->output_playback_frames_counter = 0;
	x->position = x->samplestart;
	x->note_stopped = 0;
	x->playback_direction = PLAYBACK_DIRECTION_FORWARD;
}

void samplelooper_tilde_on_note_off(t_samplelooper_tilde *x){
	x->note_stopped = 1;
}

void samplelooper_tilde_enable_lfo(t_samplelooper_tilde *x, t_floatarg argument){
	t_int lfo_enabled = (t_int)argument;
	if(lfo_enabled == 0 || lfo_enabled == 1){
		x->lfo_enabled = lfo_enabled;
	}
}

void samplelooper_tilde_loop_mode(t_samplelooper_tilde *x, t_floatarg argument){
	x->loop_mode = (t_int)argument;
	post("x->loop_mode samplelooper: %d", x->loop_mode);
}

void output_playback_frames(t_samplelooper_tilde *x){
	t_atom playback_frames[4];
	SETFLOAT(playback_frames, (t_float)x->playback_frames_start);
	SETFLOAT(playback_frames+1, (t_float)x->playback_frames_end);
	SETFLOAT(playback_frames+2, (t_float)x->processed_seconds);
	SETFLOAT(playback_frames+3, (t_float)x->note_stopped);
	outlet_list(x->playback_frames_out, gensym("list"), 4, playback_frames);
}

void samplelooper_tilde_free(t_samplelooper_tilde *x){
  	outlet_free(x->index_out);
	outlet_free(x->playback_frames_out);
	outlet_free(x->playback_direction_out);
	outlet_free(x->finished_out);
	inlet_free(x->samplestart_in);
	inlet_free(x->sampleend_in);
	inlet_free(x->loopstart_in);
	inlet_free(x->loopend_in);
} 

void *samplelooper_tilde_new(t_floatarg output_playback_frames){
  	t_samplelooper_tilde *x = (t_samplelooper_tilde *)pd_new(samplelooper_tilde_class);
	x->output_playback_frames = output_playback_frames;
	x->samplestart_in = floatinlet_new(&x->x_obj, &x->samplestart);
	x->sampleend_in = floatinlet_new(&x->x_obj, &x->sampleend);
	x->loopstart_in = floatinlet_new(&x->x_obj, &x->loopstart);
	x->loopend_in = floatinlet_new(&x->x_obj, &x->loopend);
	x->seamsize_ratio_in = floatinlet_new(&x->x_obj, &x->seamsize_ratio);

	x->index_out = outlet_new(&x->x_obj, &s_signal);
	x->playback_direction_out = outlet_new(&x->x_obj, &s_signal); 
	x->playback_frames_out = outlet_new(&x->x_obj, &s_list); 
	x->finished_out = outlet_new(&x->x_obj, &s_bang); 

	pdsr = sys_getsr();

  	return (void *)x;
}

void samplelooper_tilde_loop_none(t_samplelooper_tilde* x, t_float* in, t_float* out, int n){
	t_float position = x->position;
	t_float pitch_ratio = (t_float)x->pitch_ratio;
	t_float loopstart = x->loopstart;
	t_float sig_pitch;
	while (n--){
		t_float sig = *in++;
		sig_pitch = (x->lfo_enabled == 1) ? (1-sig) : 1;
		if(position >= x->sampleend){
			x->note_stopped = 1;
			position = x->sampleend - 1;
			x->playback_frames_end = position;
			x->position = x->samplestart;
			outlet_bang(x->finished_out);
			break;
		}
		x->playback_frames_end = position;
		*out++ = position;
		position += pitch_ratio * sig_pitch; 
	}
	x->position = position;
}

void samplelooper_tilde_loop_forward(t_samplelooper_tilde* x, t_float* in, t_float* out_position, t_float* out_direction, int n){
	t_float position = x->position;
	t_float pitch_ratio = (t_float)x->pitch_ratio;
	t_float loopstart = x->loopstart;
	t_float sig_pitch;
	while (n--){
		t_float sig = *in++;
		sig_pitch = (x->lfo_enabled == 1) ? (1-sig) : 1;	
		t_float seamsize = (x->loopend - x->loopstart) * x->seamsize_ratio;
		t_float loopend = x->loopend - seamsize;
		if(position >= loopend){
			float range = loopend - loopstart;
			position = fmod(position - loopstart, range) + loopstart;
		}
		x->playback_frames_end = position;
		*out_position++ = position;
		*out_direction++ = PLAYBACK_DIRECTION_FORWARD;
		position += pitch_ratio * sig_pitch; 
	}
	x->position = position;
}

void samplelooper_tilde_loop_backward(t_samplelooper_tilde* x, t_float* in, t_float* out_position,  t_float* out_direction, int n){
	t_float position = x->position;
	t_float pitch_ratio = (t_float)x->pitch_ratio;
	t_float loopstart = x->loopstart;
	t_float sig_pitch;

	while (n--){
		t_float sig = *in++;
		sig_pitch = (x->lfo_enabled == 1) ? (1-sig) : 1;
		t_float seamsize = (x->loopend - x->loopstart) * x->seamsize_ratio;
		t_float loopend = x->loopend - seamsize;
		if(x->playback_direction == PLAYBACK_DIRECTION_FORWARD && position >= loopend){
			x->playback_direction = PLAYBACK_DIRECTION_BACKWARD;
		}
		if(x->playback_direction == PLAYBACK_DIRECTION_BACKWARD && position <= loopstart){
			float range = loopend - loopstart;
			position = loopend - fmod(loopend - position, range);
		}
		x->playback_frames_end = position;
		*out_position++ = position;
		t_float position_change = pitch_ratio * sig_pitch;
		position_change *= x->playback_direction == PLAYBACK_DIRECTION_BACKWARD ? -1 : 1;
		position += position_change; 
	}

	x->position = position;
}

void samplelooper_tilde_loop_pingpong(t_samplelooper_tilde* x, t_float* in, t_float* out_position, t_float* out_direction, int n){
	t_float position = x->position;
	t_int playback_direction = x->playback_direction;
	t_float pitch_ratio = (t_float)x->pitch_ratio;
	t_float loopstart = x->loopstart;
	t_float sig_pitch;

	while (n--){
		t_float sig = *in++;
		sig_pitch = (x->lfo_enabled == 1) ? (1-sig) : 1;
		t_float seamsize = (t_int)((x->loopend - x->loopstart) * x->seamsize_ratio);
		if(x->playback_direction == PLAYBACK_DIRECTION_FORWARD){
			if(position >= x->loopend - seamsize/2){
				x->playback_direction = PLAYBACK_DIRECTION_BACKWARD;
			}
		}
		if(x->playback_direction == PLAYBACK_DIRECTION_BACKWARD){
			if(position <= x->loopstart + seamsize/2){
				x->playback_direction = PLAYBACK_DIRECTION_FORWARD;
			}
		}
		x->playback_frames_end = position;
		*out_position++ = position;
		*out_direction++ = x->playback_direction;
		position += pitch_ratio * sig_pitch * (x->playback_direction == PLAYBACK_DIRECTION_BACKWARD ? -1 : 1);
	}

	x->position = position;
}

t_int* samplelooper_tilde_perform(t_int* w){
	t_samplelooper_tilde* x = (t_samplelooper_tilde*)(w[1]);
	t_float* in = (t_float*)(w[2]); /* inlet */
	t_float* out_position = (t_float*)(w[3]); /* outlet */
	t_float* out_direction = (t_float*)(w[4]); /* outlet */
	int n = (int)(w[5]);
	
	if(x->output_playback_frames_counter == 0){
		x->playback_frames_start = x->position;
		x->playback_frames_end = x->position;
	}

	x->processed_seconds += (t_float)n/(t_float)pdsr;
	x->output_playback_frames_counter += x->output_playback_frames_counter >= 0 ? 1 : 0;

	if(x->loop_mode == LOOP_MODE_NONE){
		samplelooper_tilde_loop_none(x, in, out_position, n);
	}

	if(x->loop_mode == LOOP_MODE_FORWARD){
		samplelooper_tilde_loop_forward(x, in, out_position, out_direction, n);
	}

	/*if(x->loop_mode == LOOP_MODE_BACKWARD){
		samplelooper_tilde_loop_backward(x, in, out_position, n);
	}*/

	if(x->loop_mode == LOOP_MODE_PINGPONG){
		samplelooper_tilde_loop_pingpong(x, in, out_position, out_direction, n);
	}

	if(x->output_playback_frames == 1 && (x->output_playback_frames_counter >= output_playback_frames_every || x->note_stopped == 1)){
		if(x->output_playback_frames_counter >= 0) output_playback_frames(x);
		//set x->output_playback_frames_counter to negative if note is stopped, so we don't keep on sending stop messages
		x->output_playback_frames_counter = x->note_stopped == 1 ? -1 : 0;
	}

	return (w+6);
}

void samplelooper_tilde_dsp(t_samplelooper_tilde* x, t_signal**sp){
  	dsp_add(samplelooper_tilde_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
}


void samplelooper_tilde_setup(void){

	samplelooper_tilde_class = class_new(
		gensym("samplelooper~"),
		(t_newmethod)samplelooper_tilde_new,
		(t_method)samplelooper_tilde_free, 
		sizeof(t_samplelooper_tilde),
		CLASS_DEFAULT, 
        A_DEFFLOAT,
		0
	);

	class_addbang(samplelooper_tilde_class, samplelooper_tilde_noteon_bang);  

	class_addmethod(samplelooper_tilde_class, (t_method)samplelooper_tilde_dsp, gensym("dsp"), 0);

	class_addmethod(
		samplelooper_tilde_class, 
		(t_method)samplelooper_tilde_on_note_off, 
		gensym("onnoteoff"),
		0
	);

	class_addmethod(
		samplelooper_tilde_class, 
		(t_method)samplelooper_tilde_enable_lfo, 
		gensym("enablelfo"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		samplelooper_tilde_class, 
		(t_method)samplelooper_tilde_loop_mode, 
		gensym("loopmode"),
		A_DEFFLOAT,
		0
	);

	CLASS_MAINSIGNALIN(samplelooper_tilde_class, t_samplelooper_tilde, pitch_ratio);

}
