/*----------------------------------

Interpreted manually from output of this Faust code:

import("stdfaust.lib");
ctFreq = hslider("cutoffFrequency",500,50,10000,0.01);
q = hslider("q",5,1,30,0.1);
gain = 1;
process = _ : fi.resonlp(ctFreq,q,gain) : _;

or

process = _ : fi.resonhp(ctFreq,q,gain) : _;

or

process = _ : fi.resonbp(ctFreq,q,gain) : _;
------------------------------------*/

#include "stdlib.h"
#include "m_pd.h"
#include "math.h"

static t_class *faustreson_tilde_class;

typedef struct _faustreson_tilde {  
	t_object object_properties;
	t_float f;
	t_float fConst0;

	t_float fRec0[3];

	t_outlet *x_out1;

	t_inlet *in_freq;

	t_inlet *in_q;

	t_inlet *in_mode;

	t_float q;

	t_int mode;
	

} t_faustreson_tilde;

void *faustreson_new(t_floatarg f){
	t_faustreson_tilde *this_object = (t_faustreson_tilde *)pd_new(faustreson_tilde_class);

	this_object->fConst0 = (3.14159274f / fmin(192000.0f, fmax(1000.0f, sys_getsr())));

	this_object->x_out1 = outlet_new(&this_object->object_properties, &s_signal);
	this_object->in_freq = inlet_new(&this_object->object_properties, &this_object->object_properties.ob_pd, &s_signal, &s_signal);
	this_object->in_q = floatinlet_new (&this_object->object_properties, &this_object->q);

	this_object->mode = 0;

	return (void *)this_object;
}

t_int *faustreson_tilde_perform(t_int *w) {
	t_faustreson_tilde *this_object = (t_faustreson_tilde *)(w[1]);
	t_sample *in = (t_sample *)(w[2]); 
	t_float *frequencies = (t_float *)(w[3]);
	t_sample *out = (t_sample *)(w[4]);  
	int n = (int)(w[5]);

	t_float q = fmax(1.0f, this_object->q);

	while (n--){
		t_sample in_left = *in++;

		t_float frequency = *frequencies++;

		frequency = fmax(1.0f, frequency);
				
		if(this_object->mode == 0){

			t_float fSlow0 = (1.0f / q);
			t_float fSlow1 = tanf((this_object->fConst0 * frequency));
			t_float fSlow2 = (1.0f / fSlow1);
			t_float fSlow3 = (((fSlow0 + fSlow2) / fSlow1) + 1.0f);
			t_float fSlow4 = (1.0f / fSlow3);
			t_float fSlow5 = (1.0f / fSlow3);
			t_float fSlow6 = (((fSlow2 - fSlow0) / fSlow1) + 1.0f);
			t_float fSlow7 = (2.0f * (1.0f - (1.0f / pow(fSlow1, 2))));

			this_object->fRec0[0] = (in_left - (fSlow5 * ((fSlow6 * this_object->fRec0[2]) + (fSlow7 * this_object->fRec0[1]))));

			*out++ = (t_sample)((fSlow4 * (this_object->fRec0[2] + (this_object->fRec0[0] + (2.0f * this_object->fRec0[1])))));
		}

		if(this_object->mode == 1){

			t_float fSlow0 = 1.0f;
			t_float fSlow1 = (1.0f / q);
			t_float fSlow2 = tanf((this_object->fConst0 * frequency));
			t_float fSlow3 = (1.0f / fSlow2);
			t_float fSlow4 = (1.0f / (((fSlow1 + fSlow3) / fSlow2) + 1.0f));
			t_float fSlow5 = (((fSlow3 - fSlow1) / fSlow2) + 1.0f);
			t_float fSlow6 = (2.0f * (1.0f - (1.0f / pow(fSlow2, 2))));
			
			this_object->fRec0[0] = (in_left - (fSlow4 * ((fSlow5 * this_object->fRec0[2]) + (fSlow6 * this_object->fRec0[1]))));

			*out++ = (t_sample)((0.0f - (fSlow0 * ((fSlow4 * (this_object->fRec0[2] + (this_object->fRec0[0] + (2.0f * this_object->fRec0[1])))) - in_left))));
		}

		if(this_object->mode == 2){

			t_float fSlow0 = tanf(this_object->fConst0 * frequency);
			t_float fSlow1 = (1.0f / q);
			t_float fSlow2 = (1.0f / fSlow0);
			t_float fSlow3 = (((fSlow1 + fSlow2) / fSlow0) + 1.0f);
			t_float fSlow4 = (1.0f / (fSlow0 * fSlow3));
			t_float fSlow5 = (1.0f / fSlow3);
			t_float fSlow6 = (((fSlow2 - fSlow1) / fSlow0) + 1.0f);
			t_float fSlow7 = (2.0f * (1.0f - (1.0f / pow(fSlow0, 2))));
			t_float fSlow8 = (0.0f - fSlow4);

			this_object->fRec0[0] = (in_left - (fSlow5 * ((fSlow6 * this_object->fRec0[2]) + (fSlow7 * this_object->fRec0[1]))));

			*out++ = (t_sample)(((fSlow4 * this_object->fRec0[0]) + (fSlow8 * this_object->fRec0[2])));
		}
		
		this_object->fRec0[2] = this_object->fRec0[1];
		this_object->fRec0[1] = this_object->fRec0[0];
	}

	return (w+6);
}

void faustreson_tilde_dsp(t_faustreson_tilde *this_object, t_signal **sp){
	dsp_add(faustreson_tilde_perform, 5, this_object, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[0]->s_n);
}

void faustreson_tilde_free(t_faustreson_tilde *this_object){
	outlet_free(this_object->x_out1);
	inlet_free(this_object->in_freq);
	inlet_free(this_object->in_q);
}

void faustreson_setlp(t_faustreson_tilde *this_object, t_floatarg argument){
	this_object->mode = 0;
}

void faustreson_sethp(t_faustreson_tilde *this_object, t_floatarg argument){
	this_object->mode = 1;
}

void faustreson_setbp(t_faustreson_tilde *this_object, t_floatarg argument){
	this_object->mode = 2;
}

void faustreson_clear(t_faustreson_tilde *this_object, t_floatarg argument){
	this_object->fRec0[0] = this_object->fRec0[1] = this_object->fRec0[2] = 0.;
}

void faustreson_tilde_setup(void) {  
	faustreson_tilde_class = class_new(
		gensym("faustreson~"),  
        	(t_newmethod)faustreson_new,  
        	(t_method)faustreson_tilde_free, 
		sizeof(t_faustreson_tilde),  
        	CLASS_DEFAULT,  
        	A_DEFFLOAT, 
		0
	);

	class_addmethod(
		faustreson_tilde_class,  
		(t_method)faustreson_setlp, 
		gensym("lp"),  
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		faustreson_tilde_class,  
		(t_method)faustreson_sethp, 
		gensym("hp"),  
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		faustreson_tilde_class,  
		(t_method)faustreson_setbp, 
		gensym("bp"),  
		A_DEFFLOAT,
		0
	);

	class_addmethod(
		faustreson_tilde_class,  
		(t_method)faustreson_clear, 
		gensym("clear"),  
		A_DEFFLOAT,
		0
	);

	CLASS_MAINSIGNALIN(faustreson_tilde_class, t_faustreson_tilde, f); 
	class_addmethod(faustreson_tilde_class, (t_method) faustreson_tilde_dsp, gensym("dsp"), A_CANT);

}
