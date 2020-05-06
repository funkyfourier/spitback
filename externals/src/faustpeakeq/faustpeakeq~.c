/*----------------------------------

Interpreted manually from output of this Faust code:

import("stdfaust.lib");
freqMid = hslider("freqMid",2200,400,3500,0.1);
gainMid = hslider("gainMid",0,-48,48,0.1);
qMid = hslider("qMid",50,0,3000,0.1);

process = _ : fi.peak_eq(gainMid, freqMid, qMid) : _;



------------------------------------*/

#include "stdlib.h"
#include "m_pd.h"
#include "math.h"

static t_class *faustpeakeq_tilde_class;

typedef struct _faustpeakeq_tilde {  
	t_object object_properties;
	t_float f;

	t_outlet *x_out1;

	t_inlet *in_freq;

	t_inlet *in_gain;

	t_inlet *in_q;

	t_float gain;

	t_float freq;

	t_float q;

	t_float fRec0[3];
	t_float fConst0;
	t_float fConst1;
	t_float fConst2;
	t_float fConst3;
	t_float fConst4;

} t_faustpeakeq_tilde;

void *faustpeakeq_new(t_floatarg f){
	t_faustpeakeq_tilde *this_object = (t_faustpeakeq_tilde *)pd_new(faustpeakeq_tilde_class);

	this_object->fConst0 = fmin(192000.0f, fmax(1000.0f, sys_getsr()));
	this_object->fConst1 = (3.14159274f / this_object->fConst0);
	this_object->fConst2 = (1.0f / this_object->fConst0);
	this_object->fConst3 = (3.14159274f * this_object->fConst2);
	this_object->fConst4 = (6.28318548f * this_object->fConst2);

	this_object->x_out1 = outlet_new(&this_object->object_properties, &s_signal);
	this_object->in_freq = floatinlet_new (&this_object->object_properties, &this_object->freq);
	this_object->in_gain = floatinlet_new (&this_object->object_properties, &this_object->gain);
	this_object->in_q = floatinlet_new (&this_object->object_properties, &this_object->q);

	this_object->freq = 400.0f;
	this_object->q = 20.0f;

	return (void *)this_object;
}

t_int *faustpeakeq_tilde_perform(t_int *w) { 
	t_faustpeakeq_tilde *this_object = (t_faustpeakeq_tilde *)(w[1]);
	t_sample *in = (t_sample *)(w[2]); 
	t_sample *out = (t_sample *)(w[3]);  
	int n = (int)(w[4]);

	t_float frequency = fmax(10.0f, this_object->freq);

	t_float fSlow0 = frequency;
	t_float fSlow1 = tanf((this_object->fConst1 * fSlow0));
	t_float fSlow2 = (2.0f * (1.0f - (1.0f / powf(fSlow1, 2.0f))));
	t_float fSlow3 = (1.0f / fSlow1);
	t_float fSlow4 = this_object->gain;
	t_int iSlow5 = (fSlow4 > 0.0f);
	t_float fSlow6 = this_object->q;
	t_float fSlow7 = sinf((this_object->fConst4 * fSlow0));
	t_float fSlow8 = (this_object->fConst3 * ((fSlow6 * powf(10.0f, (0.0500000007f * fabsf(fSlow4)))) / fSlow7));
	t_float fSlow9 = (this_object->fConst3 * (fSlow6 / fSlow7));
	t_float fSlow10 = (iSlow5?fSlow9:fSlow8);
	t_float fSlow11 = ((fSlow3 * (fSlow3 - fSlow10)) + 1.0f);
	t_float fSlow12 = ((fSlow3 * (fSlow3 + fSlow10)) + 1.0f);
	t_float fSlow13 = (iSlow5?fSlow8:fSlow9);
	t_float fSlow14 = ((fSlow3 * (fSlow3 + fSlow13)) + 1.0f);
	t_float fSlow15 = (1.0f - (fSlow3 * (fSlow13 - fSlow3)));
	
	while (n--){
		t_float fTemp0 = (fSlow2 * this_object->fRec0[1]);
		this_object->fRec0[0] = (*in++ - (((this_object->fRec0[2] * fSlow11) + fTemp0) / fSlow12));
		*out++ = (t_sample)((((fTemp0 + (this_object->fRec0[0] * fSlow14)) + (this_object->fRec0[2] * fSlow15)) / fSlow12));
		this_object->fRec0[2] = this_object->fRec0[1];
		this_object->fRec0[1] = this_object->fRec0[0];
	}


	return (w+5);
}

void faustpeakeq_tilde_dsp(t_faustpeakeq_tilde *this_object, t_signal **sp){
	dsp_add(faustpeakeq_tilde_perform, 4, this_object, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void faustpeakeq_tilde_free(t_faustpeakeq_tilde *this_object){
	outlet_free(this_object->x_out1);
	inlet_free(this_object->in_freq);
	inlet_free(this_object->in_gain);
	inlet_free(this_object->in_q);
}

void faustpeakeq_tilde_setup(void) {  
	faustpeakeq_tilde_class = class_new(
		gensym("faustpeakeq~"),  
        	(t_newmethod)faustpeakeq_new,  
        	(t_method)faustpeakeq_tilde_free, 
		sizeof(t_faustpeakeq_tilde),  
        	CLASS_DEFAULT,  
        	A_DEFFLOAT, 
		0
	);

	CLASS_MAINSIGNALIN(faustpeakeq_tilde_class, t_faustpeakeq_tilde, f); 
	class_addmethod(faustpeakeq_tilde_class, (t_method) faustpeakeq_tilde_dsp, gensym("dsp"), A_CANT);

}
