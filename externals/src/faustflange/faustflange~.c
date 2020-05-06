#include "m_pd.h"
#include "math.h"

static t_class *faustflange_tilde_class;

typedef struct _faustflange_tilde {
    
    t_object  x_obj;
	t_float f;
    t_sample* in_l_buffer;
    t_sample* in_r_buffer;

    t_inlet *inlet_right;
    t_outlet *outlet_left;
    t_outlet *outlet_right;

    t_inlet *inlet_speed;
    t_inlet *inlet_feedback;
    t_inlet *inlet_width;

    t_float speed;
    t_float feedback;
    t_float width;

	int iVec0[2];
	int IOTA;
	float fVec1[8192];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fRec1[2];
	float fRec2[2];
	float fRec0[2];
	float fVec2[8192];
	float fRec3[2];

} t_faustflange_tilde;

void faustflange_instance_clear(t_faustflange_tilde *this_object){
	this_object->IOTA = 0;
    /* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			this_object->iVec0[l0] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 8192); l1 = (l1 + 1)) {
			this_object->fVec1[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			this_object->fRec1[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this_object->fRec2[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			this_object->fRec0[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 8192); l5 = (l5 + 1)) {
			this_object->fVec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			this_object->fRec3[l6] = 0.0f;
			
		}
		
	}
}

void faustflange_set_samplerate(t_faustflange_tilde *this_object){
    this_object->fSamplingFreq = (int)sys_getsr();
	this_object->fConst0 = fmin(192000.0f, fmax(1.0f, (float)this_object->fSamplingFreq));
	this_object->fConst1 = (6.28318548f / this_object->fConst0);
}

static int imax(int a, int b) { return a > b ? a : b; }

static int imin(int a, int b) { return a < b ? a : b; }

void *faustflange_new(void){

    t_faustflange_tilde *this_object = (t_faustflange_tilde *)pd_new(faustflange_tilde_class);

    this_object->inlet_right = inlet_new(&this_object->x_obj, &this_object->x_obj.ob_pd, &s_signal, &s_signal);
    this_object->inlet_speed = floatinlet_new (&this_object->x_obj, &this_object->speed);
    this_object->inlet_feedback = floatinlet_new (&this_object->x_obj, &this_object->feedback);
    this_object->inlet_width = floatinlet_new (&this_object->x_obj, &this_object->width);
    this_object->outlet_left = outlet_new(&this_object->x_obj, &s_signal);
    this_object->outlet_right = outlet_new(&this_object->x_obj, &s_signal);

    this_object->speed = 0.5;
    this_object->feedback = 0.5;
    this_object->width = 10;

    faustflange_set_samplerate(this_object);
    faustflange_instance_clear(this_object);

    return (void *)this_object;
}

void faustflange_tilde_free(t_faustflange_tilde *this_object){
    free(this_object->in_l_buffer);
    free(this_object->in_r_buffer);
}

t_int *faustflange_tilde_perform(t_int *w) {
    t_faustflange_tilde *this_object = (t_faustflange_tilde *)(w[1]);
	t_sample *inL = (t_sample *)(w[2]); 
	t_sample *inR = (t_sample *)(w[3]); 
	t_sample *outL = (t_sample *)(w[4]);
	t_sample *outR = (t_sample *)(w[5]);  
	int n = (int)(w[6]);

    for (int i = 0; (i < n); i = (i + 1)) {
        this_object->in_l_buffer[i] = inL[i];
        this_object->in_r_buffer[i] = inR[i];
    }

    float fSlow0 = (float)this_object->feedback;
	float fSlow1 = (this_object->fConst0 * (float)this_object->width);
	float fSlow2 = (this_object->fConst1 * (float)this_object->speed);
	float fSlow3 = sinf(fSlow2);
	float fSlow4 = cosf(fSlow2);
	float fSlow5 = (0.0f - fSlow3);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < n); i = (i + 1)) {
			this_object->iVec0[0] = 1;
			float fTemp0 = (float)this_object->in_l_buffer[i];
			float fTemp1 = ((fSlow0 * this_object->fRec0[1]) - fTemp0);
			this_object->fVec1[(this_object->IOTA & 8191)] = fTemp1;
			this_object->fRec1[0] = ((fSlow3 * this_object->fRec2[1]) + (fSlow4 * this_object->fRec1[1]));
			this_object->fRec2[0] = (((fSlow4 * this_object->fRec2[1]) + (fSlow5 * this_object->fRec1[1])) + (float)(1 - this_object->iVec0[1]));
			float fTemp2 = (fSlow1 * ((0.000500000024f * (this_object->fRec1[0] + 1.0f)) + 0.00100000005f));
			int iTemp3 = (int)fTemp2;
			float fTemp4 = floorf(fTemp2);
			this_object->fRec0[0] = ((this_object->fVec1[((this_object->IOTA - imin(4097, imax(0, iTemp3))) & 8191)] * (fTemp4 + (1.0f - fTemp2))) + ((fTemp2 - fTemp4) * this_object->fVec1[((this_object->IOTA - imin(4097, imax(0, (iTemp3 + 1)))) & 8191)]));
			outL[i] = (t_sample)(0.5f * (this_object->fRec0[0] + fTemp0));
			float fTemp5 = (float)this_object->in_r_buffer[i];
			float fTemp6 = ((fSlow0 * this_object->fRec3[1]) - fTemp5);
			this_object->fVec2[(this_object->IOTA & 8191)] = fTemp6;
			float fTemp7 = (fSlow1 * ((0.000500000024f * (this_object->fRec2[0] + 1.0f)) + 0.00100000005f));
			int iTemp8 = (int)fTemp7;
			float fTemp9 = floorf(fTemp7);
			this_object->fRec3[0] = ((this_object->fVec2[((this_object->IOTA - imin(4097, imax(0, iTemp8))) & 8191)] * (fTemp9 + (1.0f - fTemp7))) + ((fTemp7 - fTemp9) * this_object->fVec2[((this_object->IOTA - imin(4097, imax(0, (iTemp8 + 1)))) & 8191)]));
			outR[i] = (t_sample)(0.5f * (this_object->fRec3[0] + fTemp5));
			this_object->iVec0[1] = this_object->iVec0[0];
			this_object->IOTA = (this_object->IOTA + 1);
			this_object->fRec1[1] = this_object->fRec1[0];
			this_object->fRec2[1] = this_object->fRec2[0];
			this_object->fRec0[1] = this_object->fRec0[0];
			this_object->fRec3[1] = this_object->fRec3[0];
		}
	}

    return (w+7);
}

void faustflange_tilde_dsp(t_faustflange_tilde *this_object, t_signal **sp){
	dsp_add(faustflange_tilde_perform, 6, this_object, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);
    this_object->in_l_buffer = malloc(sp[0]->s_n * sizeof(t_sample));
    this_object->in_r_buffer = malloc(sp[0]->s_n * sizeof(t_sample));
}

void faustflange_tilde_setup(void) {
    
    faustflange_tilde_class = class_new(
		gensym("faustflange~"),  
        	(t_newmethod)faustflange_new,  
        	(t_method)faustflange_tilde_free, 
		    sizeof(t_faustflange_tilde),  
        	CLASS_DEFAULT,  
        	0
	);

    class_addmethod(
		faustflange_tilde_class,  
		(t_method)faustflange_set_samplerate, 
		gensym("samplerate"),  
		A_DEFFLOAT,
		0
	);

    CLASS_MAINSIGNALIN(faustflange_tilde_class, t_faustflange_tilde, f); 
	class_addmethod(faustflange_tilde_class, (t_method) faustflange_tilde_dsp, gensym("dsp"), A_CANT);

    class_addmethod(faustflange_tilde_class, (t_method)faustflange_instance_clear, gensym("clear"), 0);

}