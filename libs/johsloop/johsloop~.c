#include "m_pd.h"

static t_class *johsloop_tilde_class;

typedef struct _johsloop {
  	t_object  x_obj;
	t_float samplestart;
	t_float sampleend;
	t_float position;
	t_float pitch_ratio;
	t_float lfo_enabled;
} t_johsloop_tilde;

static t_float pdsr;
static t_float sig_pitch;
static t_float sig;

void johsloop_tilde_noteon_bang(t_johsloop_tilde *x){
	x->position = 0;
	//x->position = x->samplestart;
}

void johsloop_tilde_enable_lfo(t_johsloop_tilde *x){
	x->lfo_enabled = 1;
}

void johsloop_tilde_disable_lfo(t_johsloop_tilde *x){
	x->lfo_enabled = 0;
}

void *johsloop_tilde_new(void){

  	t_johsloop_tilde *x = (t_johsloop_tilde *)pd_new(johsloop_tilde_class);
	x->position = 0;
	x->samplestart = 0;
	x->sampleend = 44099;
	x->pitch_ratio = 1;
	x->lfo_enabled = 0;

	inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("bang"), gensym("noteon_bang"));
	
	floatinlet_new(&x->x_obj, &x->samplestart);
	floatinlet_new(&x->x_obj, &x->sampleend);

	outlet_new(&x->x_obj, &s_signal);

  	return (void *)x;
}

t_int *johsloop_tilde_perform(t_int *w){
	t_johsloop_tilde *x = (t_johsloop_tilde *)(w[1]);
	t_float  *in = (t_float *)(w[2]); /* inlet */
	t_float  *out = (t_float *)(w[3]); /* outlet */
	int n = (int)(w[4]);
	
	while (n--){
		sig = *in++;
		
		sig_pitch = (x->lfo_enabled == 1) ? (1-sig) : 1;	

		if(x->position >= x->sampleend){
			//post("%f", x->position);
			x->position = x->samplestart;
		}
		
		*out++ = (x->position);

		x->position += x->pitch_ratio * sig_pitch; 

		if(x->position > x->sampleend){
			x->position = x->sampleend;
		}
	}		

	return (w+5);
}

void johsloop_tilde_dsp(t_johsloop_tilde *x, t_signal **sp){
  	dsp_add(johsloop_tilde_perform, 4, x, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}


void johsloop_tilde_setup(void){

	pdsr = sys_getsr();

	johsloop_tilde_class = class_new(
		gensym("johsloop~"),
		(t_newmethod)johsloop_tilde_new,
		0, 
		sizeof(t_johsloop_tilde),
		CLASS_DEFAULT, 
		0
	);

	class_addmethod(johsloop_tilde_class, (t_method)johsloop_tilde_dsp, gensym("dsp"), 0);

	class_addmethod(johsloop_tilde_class, (t_method)johsloop_tilde_noteon_bang, gensym("noteon_bang"), 0);

	class_addmethod(johsloop_tilde_class, (t_method)johsloop_tilde_enable_lfo, gensym("enable"), 0);
	class_addmethod(johsloop_tilde_class, (t_method)johsloop_tilde_disable_lfo, gensym("disable"), 0);

	CLASS_MAINSIGNALIN(johsloop_tilde_class, t_johsloop_tilde, pitch_ratio);

}
