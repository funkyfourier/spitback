#include "m_pd.h"
#include <stdlib.h>
#include "math.h"

static t_class *faustdelay_tilde_class;

typedef struct _faustdelay_tilde
{

    t_object x_obj;
    t_float f;
    t_sample *in_l_buffer;
    t_sample *in_r_buffer;

    t_inlet *inlet_right;
    t_inlet *inlet_delay;
    t_inlet *inlet_feedback;
    t_inlet *inlet_wet;

    t_outlet *outlet_left;
    t_outlet *outlet_right;
    t_outlet *outlet_left_delay;
    t_outlet *outlet_right_delay;

    t_float delay;
    t_float feedback;
    t_float wet;

    t_int IOTA;
    t_float fVec0[524288];
    t_int fSamplingFreq;
    t_float fConst0;
    t_int iConst1;
    t_float fConst2;
    t_float fRec1[2];
    t_float fRec0[524288];
    t_float fVec1[524288];
    t_float fRec2[524288];

} t_faustdelay_tilde;

void faustdelay_instance_clear(t_faustdelay_tilde *this_object)
{
    this_object->IOTA = 0;
    /* C99 loop */
    {
        int l0;
        for (l0 = 0; (l0 < 524288); l0 = (l0 + 1))
        {
            this_object->fVec0[l0] = 0.0f;
        }
    }
    /* C99 loop */
    {
        int l1;
        for (l1 = 0; (l1 < 2); l1 = (l1 + 1))
        {
            this_object->fRec1[l1] = 0.0f;
        }
    }
    /* C99 loop */
    {
        int l2;
        for (l2 = 0; (l2 < 524288); l2 = (l2 + 1))
        {
            this_object->fRec0[l2] = 0.0f;
        }
    }
    /* C99 loop */
    {
        int l3;
        for (l3 = 0; (l3 < 524288); l3 = (l3 + 1))
        {
            this_object->fVec1[l3] = 0.0f;
        }
    }
    /* C99 loop */
    {
        int l4;
        for (l4 = 0; (l4 < 524288); l4 = (l4 + 1))
        {
            this_object->fRec2[l4] = 0.0f;
        }
    }
}

static int imax(int a, int b) { return a > b ? a : b; }

static int imin(int a, int b) { return a < b ? a : b; }

void *faustdelay_new(void)
{

    t_faustdelay_tilde *this_object = (t_faustdelay_tilde *)pd_new(faustdelay_tilde_class);

    this_object->inlet_right = inlet_new(&this_object->x_obj, &this_object->x_obj.ob_pd, &s_signal, &s_signal);
    this_object->inlet_delay = floatinlet_new(&this_object->x_obj, &this_object->delay);
    this_object->inlet_feedback = floatinlet_new(&this_object->x_obj, &this_object->feedback);
    this_object->inlet_wet = floatinlet_new(&this_object->x_obj, &this_object->wet);
    this_object->outlet_left = outlet_new(&this_object->x_obj, &s_signal);
    this_object->outlet_right = outlet_new(&this_object->x_obj, &s_signal);
    this_object->outlet_left_delay = outlet_new(&this_object->x_obj, &s_signal);
    this_object->outlet_right_delay = outlet_new(&this_object->x_obj, &s_signal);

    this_object->delay = 100;
    this_object->feedback = 0.7;
    this_object->wet = 0.5;

    faustdelay_instance_clear(this_object);

    this_object->fSamplingFreq = (t_int)sys_getsr();
    this_object->fConst0 = fmin(192000.0f, fmax(1.0f, (float)this_object->fSamplingFreq));
    this_object->iConst1 = (int)(2.0f * this_object->fConst0);
    this_object->fConst2 = (0.00100000005f * this_object->fConst0);

    return (void *)this_object;
}

void faustdelay_tilde_free(t_faustdelay_tilde *this_object)
{
    free(this_object->in_l_buffer);
    free(this_object->in_r_buffer);
    /*free(this_object->fVec0);
    free(this_object->fRec1);
    free(this_object->fRec0);
    free(this_object->fVec1);
    free(this_object->fRec2);*/
}

t_int *faustdelay_tilde_perform(t_int *w)
{
    t_faustdelay_tilde *this_object = (t_faustdelay_tilde *)(w[1]);
    t_sample *inL = (t_sample *)(w[2]);
    t_sample *inR = (t_sample *)(w[3]);
    t_sample *outL = (t_sample *)(w[4]);
    t_sample *outR = (t_sample *)(w[5]);
    t_sample *outLDelay = (t_sample *)(w[6]);
    t_sample *outRDelay = (t_sample *)(w[7]);
    int n = (int)(w[8]);

    for (int i = 0; (i < n); i = (i + 1))
    {
        this_object->in_l_buffer[i] = inL[i];
        this_object->in_r_buffer[i] = inR[i];
    }

    float fSlow0 = (float)this_object->wet;
	float fSlow1 = (float)this_object->feedback;
	float fSlow2 = (0.00100000005f * (float)this_object->delay);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < n); i = (i + 1)) {
			float fTemp0 = (float)this_object->in_l_buffer[i];
			this_object->fVec0[(this_object->IOTA & 524287)] = fTemp0;
			outL[i] = (t_sample)fTemp0;
			this_object->fRec1[0] = (fSlow2 + (0.999000013f * this_object->fRec1[1]));
			int iTemp1 = (int)(this_object->fConst2 * this_object->fRec1[0]);
			int iTemp2 = imin(this_object->iConst1, imax(0, (2 * iTemp1)));
			int iTemp3 = (iTemp2 + 1);
			this_object->fRec0[(this_object->IOTA & 524287)] = (fSlow1 * (this_object->fRec0[((this_object->IOTA - iTemp3) & 524287)] + this_object->fVec0[((this_object->IOTA - imin(this_object->iConst1, imax(0, iTemp1))) & 524287)]));
			outLDelay[i] = (t_sample)(fSlow0 * this_object->fRec0[((this_object->IOTA - 0) & 524287)]);
			float fTemp4 = (float)this_object->in_r_buffer[i];
			this_object->fVec1[(this_object->IOTA & 524287)] = fTemp4;
			this_object->fRec2[(this_object->IOTA & 524287)] = (fSlow1 * (this_object->fRec2[((this_object->IOTA - iTemp3) & 524287)] + this_object->fVec1[((this_object->IOTA - iTemp2) & 524287)]));
			outR[i] = (t_sample)(fSlow0 * this_object->fRec2[((this_object->IOTA - 0) & 524287)]);
			outRDelay[i] = (t_sample)fTemp4;
			this_object->IOTA = (this_object->IOTA + 1);
			this_object->fRec1[1] = this_object->fRec1[0];
			
		}
		
	}

    return (w + 9);
}

void faustdelay_tilde_dsp(t_faustdelay_tilde *this_object, t_signal **sp)
{
    dsp_add(
        faustdelay_tilde_perform,
        8,
        this_object,
        sp[0]->s_vec,
        sp[1]->s_vec,
        sp[2]->s_vec,
        sp[3]->s_vec,
        sp[4]->s_vec,
        sp[5]->s_vec,
        sp[0]->s_n);
    this_object->in_l_buffer = malloc(sp[0]->s_n * sizeof(t_sample));
    this_object->in_r_buffer = malloc(sp[0]->s_n * sizeof(t_sample));
}

void faustdelay_tilde_setup(void)
{

    faustdelay_tilde_class = class_new(
        gensym("faustdelay~"),
        (t_newmethod)faustdelay_new,
        (t_method)faustdelay_tilde_free,
        sizeof(t_faustdelay_tilde),
        CLASS_DEFAULT,
        0);

    CLASS_MAINSIGNALIN(faustdelay_tilde_class, t_faustdelay_tilde, f);
    class_addmethod(faustdelay_tilde_class, (t_method)faustdelay_tilde_dsp, gensym("dsp"), A_CANT);

    class_addmethod(faustdelay_tilde_class, (t_method)faustdelay_instance_clear, gensym("clear"), 0);
}