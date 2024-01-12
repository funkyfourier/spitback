#include "m_pd.h"

static t_class* seamless_tilde_class;

typedef struct _seamless {
  	t_object x_obj;
	t_float signal_inlet_dummy;
	t_float seamsize;
	t_float loopstart;
	t_float loopend;
	t_float loop_enabled;
	t_outlet* outlet_index_0;
	t_outlet* outlet_index_1;
	t_inlet* inlet_seamsize;
	t_inlet* inlet_loopstart;
	t_inlet* inlet_loopend;
	t_inlet* inlet_loopenabled
} t_seamless_tilde;

void seamless_tilde_free(t_seamless_tilde* x){
	inlet_free(x->inlet_seamsize);
	inlet_free(x->inlet_loopstart);
	inlet_free(x->inlet_loopend);
	outlet_free(x->inlet_loopenabled);
	outlet_free(x->outlet_index_0);
	outlet_free(x->outlet_index_1);
}

void *seamless_tilde_new(){
	t_seamless_tilde* x = (t_seamless_tilde*)pd_new(seamless_tilde_class);
	x->inlet_seamsize = floatinlet_new(&x->x_obj, &x->seamsize);
	x->inlet_loopstart = floatinlet_new(&x->x_obj, &x->loopstart);
	x->inlet_loopend = floatinlet_new(&x->x_obj, &x->loopend);
	x->inlet_loopenabled = floatinlet_new(&x->x_obj, &x->loop_enabled);
    x->outlet_index_0 = outlet_new(&x->x_obj, &s_signal);
    x->outlet_index_1 = outlet_new(&x->x_obj, &s_signal);
	return (void*)x;
}

t_int *seamless_tilde_perform(t_int *w){
	t_seamless_tilde* x = (t_seamless_tilde*)(w[1]);
	t_sample* in1 =      (t_sample*)(w[2]);
	t_sample* out_index_0 = (t_sample *)(w[3]);
	t_sample* out_index_1 = (t_sample *)(w[4]);
	int n = (int)(w[5]);

	t_int loop_enabled = (t_int)x->loop_enabled;

	post("perform seamsize: %f loopstart: %f loopend: %f loopenabled: %d", x->seamsize, x->loopstart, x->loopend, loop_enabled);

	while (n--){

		*out_index_0++ = 3;
		*out_index_1++ = 3;

	}

	 return (w+6);
}

void seamless_tilde_dsp(t_seamless_tilde *x, t_signal **sp){
  	dsp_add(seamless_tilde_perform, 5, x, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
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

}