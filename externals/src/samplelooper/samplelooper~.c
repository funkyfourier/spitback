#include "m_pd.h"
#include <math.h>

static t_class *samplelooper_tilde_class;

typedef struct _samplelooper {
  	t_object  x_obj;
	t_float samplestart;
	t_float sampleend;
	t_float loopstart;
	t_float loopend;
	double position;
	t_float pitch_ratio;
	t_int lfo_enabled;
	t_int loop_enabled;
	t_outlet *index_out;
	t_outlet *start_frame_out;
	t_outlet *finished_out;
	t_inlet *samplestart_in;
	t_inlet *sampleend_in;
	t_inlet *loopstart_in;
	t_inlet *loopend_in;
} t_samplelooper_tilde;

static t_float pdsr;

void samplelooper_tilde_noteon_bang(t_samplelooper_tilde *x){
	x->position = x->samplestart;
	outlet_float(x->start_frame_out, x->position);
}

void samplelooper_tilde_enable_lfo(t_samplelooper_tilde *x, t_floatarg argument){
	t_int lfo_enabled = (t_int)argument;
	if(lfo_enabled == 0 || lfo_enabled == 1){
		x->lfo_enabled = lfo_enabled;
	}
}

void samplelooper_tilde_enable_loop(t_samplelooper_tilde *x, t_floatarg argument){
	t_int loop_enabled = (t_int)argument;
	if(loop_enabled == 0 || loop_enabled == 1){
		x->loop_enabled = loop_enabled;
	}
}

void samplelooper_tilde_disable_loop(t_samplelooper_tilde *x){
	x->loop_enabled = 0; 
}

void samplelooper_tilde_free(t_samplelooper_tilde *x){
  	outlet_free(x->index_out);
	outlet_free(x->start_frame_out);
	outlet_free(x->finished_out);
	inlet_free(x->samplestart_in);
	inlet_free(x->sampleend_in);
	inlet_free(x->loopstart_in);
	inlet_free(x->loopend_in);
} 

void *samplelooper_tilde_new(void){

  	t_samplelooper_tilde *x = (t_samplelooper_tilde *)pd_new(samplelooper_tilde_class);
	x->position = 0;
	x->samplestart = 0;
	x->sampleend = 44099;
	x->loopstart = 0;
	x->loopend = 44099;
	x->pitch_ratio = 1;
	x->lfo_enabled = 0;
	x->loop_enabled = 0;
	
	x->samplestart_in = floatinlet_new(&x->x_obj, &x->samplestart);
	x->sampleend_in = floatinlet_new(&x->x_obj, &x->sampleend);

	x->loopstart_in = floatinlet_new(&x->x_obj, &x->loopstart);
	x->loopend_in = floatinlet_new(&x->x_obj, &x->loopend);

	x->index_out = outlet_new(&x->x_obj, &s_signal);

	x->start_frame_out = outlet_new(&x->x_obj, &s_float); 

	x->finished_out = outlet_new(&x->x_obj, &s_bang); 

  	return (void *)x;
}

t_int *samplelooper_tilde_perform(t_int *w){
	t_samplelooper_tilde *x = (t_samplelooper_tilde *)(w[1]);
	t_float  *in = (t_float *)(w[2]); /* inlet */
	t_float  *out = (t_float *)(w[3]); /* outlet */
	int n = (int)(w[4]);

	double position = x->position;
	double pitch_ratio = (double)x->pitch_ratio;
	float loopstart = x->loopstart;
    float loopend = x->loopend;
	
	while (n--){
		double sig = *in++;
		double sig_pitch = (x->lfo_enabled == 1) ? (1-sig) : 1;	
		if(x->loop_enabled == 1){
			if(position >= loopend){
				float range = loopend - loopstart;
				position = fmod(position - loopstart, range) + loopstart;
				outlet_float(x->start_frame_out, position);
			}
		}
		else {
			if(x->position >= x->sampleend){
				x->position = x->samplestart;
				outlet_bang(x->finished_out);
			}
		}
		*out++ = (position);
		position += pitch_ratio * sig_pitch; 
	}

	x->position = position;

	return (w+5);
}

void samplelooper_tilde_dsp(t_samplelooper_tilde *x, t_signal **sp){
  	dsp_add(samplelooper_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}


void samplelooper_tilde_setup(void){

	pdsr = sys_getsr();

	samplelooper_tilde_class = class_new(
		gensym("samplelooper~"),
		(t_newmethod)samplelooper_tilde_new,
		(t_method)samplelooper_tilde_free, 
		sizeof(t_samplelooper_tilde),
		CLASS_DEFAULT, 
		0
	);

	class_addbang(samplelooper_tilde_class, samplelooper_tilde_noteon_bang);  

	class_addmethod(samplelooper_tilde_class, (t_method)samplelooper_tilde_dsp, gensym("dsp"), 0);

	class_addmethod(
		samplelooper_tilde_class, 
		(t_method)samplelooper_tilde_enable_lfo, 
		gensym("enablelfo"),
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		samplelooper_tilde_class, 
		(t_method)samplelooper_tilde_enable_loop, 
		gensym("enableloop"),
		A_DEFFLOAT,
		0
	);

	CLASS_MAINSIGNALIN(samplelooper_tilde_class, t_samplelooper_tilde, pitch_ratio);

}
