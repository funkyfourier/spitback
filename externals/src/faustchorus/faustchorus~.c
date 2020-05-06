#include "m_pd.h"
#include "math.h"

static t_class *faustchorus_tilde_class;

typedef struct _faustchorus_tilde
{

	t_object x_obj;
	t_float f;
	t_sample *in_l_buffer;
	t_sample *in_r_buffer;

	t_inlet *inlet_right;
	t_outlet *outlet0;
	t_outlet *outlet1;
	t_outlet *outlet2;
	t_outlet *outlet3;

	t_inlet *inlet_freq;
	t_inlet *inlet_depth;

	t_float freq;
	t_float depth;

	int IOTA;
	float fVec0[8192];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	int iVec1[2];
	float fRec0[2];
	float fConst2;
	float fRec1[2];
	float fRec2[2];
	float fVec2[8192];
	float fConst3;
	float fRec3[2];
	float fRec4[2];
	float fConst4;
	float fRec5[2];
	float fRec6[2];
	float fConst5;
	float fRec7[2];
	float fRec8[2];

} t_faustchorus_tilde;

void faustchorus_instance_clear(t_faustchorus_tilde *this_object)
{
	this_object->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 8192); l0 = (l0 + 1))
		{
			this_object->fVec0[l0] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1))
		{
			this_object->iVec1[l1] = 0;
		}
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1))
		{
			this_object->fRec0[l2] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1))
		{
			this_object->fRec1[l3] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1))
		{
			this_object->fRec2[l4] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 8192); l5 = (l5 + 1))
		{
			this_object->fVec2[l5] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1))
		{
			this_object->fRec3[l6] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1))
		{
			this_object->fRec4[l7] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1))
		{
			this_object->fRec5[l8] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1))
		{
			this_object->fRec6[l9] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1))
		{
			this_object->fRec7[l10] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1))
		{
			this_object->fRec8[l11] = 0.0f;
		}
	}
}

void faustchorus_set_samplerate(t_faustchorus_tilde *this_object)
{
	this_object->fSamplingFreq = (int)sys_getsr();
	this_object->fConst0 = fmin(192000.0f, fmax(1.0f, (float)this_object->fSamplingFreq));
	this_object->fConst1 = (0.00100000005f * (float)(int)(0.0116099771f * this_object->fConst0));
	this_object->fConst2 = (6.28318548f / this_object->fConst0);
	this_object->fConst3 = (3.14159274f / this_object->fConst0);
	this_object->fConst4 = (2.09439516f / this_object->fConst0);
	this_object->fConst5 = (1.57079637f / this_object->fConst0);
}

static int imax(int a, int b) { return a > b ? a : b; }

static int imin(int a, int b) { return a < b ? a : b; }

void *faustchorus_new(void)
{

	t_faustchorus_tilde *this_object = (t_faustchorus_tilde *)pd_new(faustchorus_tilde_class);

	this_object->inlet_right = inlet_new(&this_object->x_obj, &this_object->x_obj.ob_pd, &s_signal, &s_signal);
	this_object->inlet_freq = floatinlet_new(&this_object->x_obj, &this_object->freq);
	this_object->inlet_depth = floatinlet_new(&this_object->x_obj, &this_object->depth);
	this_object->outlet0 = outlet_new(&this_object->x_obj, &s_signal);
	this_object->outlet1 = outlet_new(&this_object->x_obj, &s_signal);
	this_object->outlet2 = outlet_new(&this_object->x_obj, &s_signal);
	this_object->outlet3 = outlet_new(&this_object->x_obj, &s_signal);

	faustchorus_set_samplerate(this_object);
	faustchorus_instance_clear(this_object);

	return (void *)this_object;
}

void faustchorus_tilde_free(t_faustchorus_tilde *this_object)
{
	free(this_object->in_l_buffer);
	free(this_object->in_r_buffer);
}

t_int *faustchorus_tilde_perform(t_int *w)
{
	t_faustchorus_tilde *this_object = (t_faustchorus_tilde *)(w[1]);
	t_sample *inL = (t_sample *)(w[2]);
	t_sample *inR = (t_sample *)(w[3]);
	t_sample *output0 = (t_sample *)(w[4]);
	t_sample *output1 = (t_sample *)(w[5]);
	t_sample *output2 = (t_sample *)(w[6]);
	t_sample *output3 = (t_sample *)(w[7]);
	int n = (int)(w[8]);

	for (int i = 0; (i < n); i = (i + 1))
	{
		this_object->in_l_buffer[i] = inL[i];
		this_object->in_r_buffer[i] = inR[i];
	}

	float fSlow0 = (this_object->fConst1 * (float)this_object->depth);
	float fSlow1 = (float)this_object->freq;
	float fSlow2 = (this_object->fConst2 * fSlow1);
	float fSlow3 = sinf(fSlow2);
	float fSlow4 = cosf(fSlow2);
	float fSlow5 = (0.0f - fSlow3);
	float fSlow6 = (this_object->fConst3 * fSlow1);
	float fSlow7 = sinf(fSlow6);
	float fSlow8 = cosf(fSlow6);
	float fSlow9 = (0.0f - fSlow7);
	float fSlow10 = (this_object->fConst4 * fSlow1);
	float fSlow11 = sinf(fSlow10);
	float fSlow12 = cosf(fSlow10);
	float fSlow13 = (0.0f - fSlow11);
	float fSlow14 = (this_object->fConst5 * fSlow1);
	float fSlow15 = sinf(fSlow14);
	float fSlow16 = cosf(fSlow14);
	float fSlow17 = (0.0f - fSlow15);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < n); i = (i + 1))
		{
			float fTemp0 = (float)this_object->in_l_buffer[i];
			this_object->fVec0[(this_object->IOTA & 8191)] = fTemp0;
			this_object->iVec1[0] = 1;
			this_object->fRec0[0] = (fSlow0 + (0.999000013f * this_object->fRec0[1]));
			this_object->fRec1[0] = ((fSlow3 * this_object->fRec2[1]) + (fSlow4 * this_object->fRec1[1]));
			int iTemp1 = (1 - this_object->iVec1[1]);
			this_object->fRec2[0] = (((fSlow4 * this_object->fRec2[1]) + (fSlow5 * this_object->fRec1[1])) + (float)iTemp1);
			float fTemp2 = (this_object->fRec0[0] * (this_object->fRec1[0] + 1.0f));
			int iTemp3 = (int)fTemp2;
			float fTemp4 = floorf(fTemp2);
			output0[i] = (t_sample)((this_object->fVec0[((this_object->IOTA - imin(4097, imax(0, iTemp3))) & 8191)] * (fTemp4 + (1.0f - fTemp2))) + ((fTemp2 - fTemp4) * this_object->fVec0[((this_object->IOTA - imin(4097, imax(0, (iTemp3 + 1)))) & 8191)]));
			float fTemp5 = (float)this_object->in_r_buffer[i];
			this_object->fVec2[(this_object->IOTA & 8191)] = fTemp5;
			this_object->fRec3[0] = ((fSlow7 * this_object->fRec4[1]) + (fSlow8 * this_object->fRec3[1]));
			this_object->fRec4[0] = (((fSlow8 * this_object->fRec4[1]) + (fSlow9 * this_object->fRec3[1])) + (float)iTemp1);
			float fTemp6 = (this_object->fRec0[0] * (this_object->fRec3[0] + 1.0f));
			int iTemp7 = (int)fTemp6;
			float fTemp8 = floorf(fTemp6);
			output1[i] = (t_sample)((this_object->fVec2[((this_object->IOTA - imin(4097, imax(0, iTemp7))) & 8191)] * (fTemp8 + (1.0f - fTemp6))) + ((fTemp6 - fTemp8) * this_object->fVec2[((this_object->IOTA - imin(4097, imax(0, (iTemp7 + 1)))) & 8191)]));
			this_object->fRec5[0] = ((fSlow11 * this_object->fRec6[1]) + (fSlow12 * this_object->fRec5[1]));
			this_object->fRec6[0] = (((fSlow12 * this_object->fRec6[1]) + (fSlow13 * this_object->fRec5[1])) + (float)iTemp1);
			float fTemp9 = (this_object->fRec0[0] * (this_object->fRec5[0] + 1.0f));
			int iTemp10 = (int)fTemp9;
			float fTemp11 = floorf(fTemp9);
			output2[i] = (t_sample)((this_object->fVec0[((this_object->IOTA - imin(4097, imax(0, iTemp10))) & 8191)] * (fTemp11 + (1.0f - fTemp9))) + ((fTemp9 - fTemp11) * this_object->fVec0[((this_object->IOTA - imin(4097, imax(0, (iTemp10 + 1)))) & 8191)]));
			this_object->fRec7[0] = ((fSlow15 * this_object->fRec8[1]) + (fSlow16 * this_object->fRec7[1]));
			this_object->fRec8[0] = (((fSlow16 * this_object->fRec8[1]) + (fSlow17 * this_object->fRec7[1])) + (float)iTemp1);
			float fTemp12 = (this_object->fRec0[0] * (this_object->fRec7[0] + 1.0f));
			int iTemp13 = (int)fTemp12;
			float fTemp14 = floorf(fTemp12);
			output3[i] = (t_sample)((this_object->fVec2[((this_object->IOTA - imin(4097, imax(0, iTemp13))) & 8191)] * (fTemp14 + (1.0f - fTemp12))) + ((fTemp12 - fTemp14) * this_object->fVec2[((this_object->IOTA - imin(4097, imax(0, (iTemp13 + 1)))) & 8191)]));
			this_object->IOTA = (this_object->IOTA + 1);
			this_object->iVec1[1] = this_object->iVec1[0];
			this_object->fRec0[1] = this_object->fRec0[0];
			this_object->fRec1[1] = this_object->fRec1[0];
			this_object->fRec2[1] = this_object->fRec2[0];
			this_object->fRec3[1] = this_object->fRec3[0];
			this_object->fRec4[1] = this_object->fRec4[0];
			this_object->fRec5[1] = this_object->fRec5[0];
			this_object->fRec6[1] = this_object->fRec6[0];
			this_object->fRec7[1] = this_object->fRec7[0];
			this_object->fRec8[1] = this_object->fRec8[0];
		}
	}

	return (w + 9);
}

void faustchorus_tilde_dsp(t_faustchorus_tilde *this_object, t_signal **sp)
{
	dsp_add(
		faustchorus_tilde_perform,
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

void faustchorus_tilde_setup(void)
{

	faustchorus_tilde_class = class_new(
		gensym("faustchorus~"),
		(t_newmethod)faustchorus_new,
		(t_method)faustchorus_tilde_free,
		sizeof(t_faustchorus_tilde),
		CLASS_DEFAULT,
		0);

	class_addmethod(
		faustchorus_tilde_class,
		(t_method)faustchorus_set_samplerate,
		gensym("samplerate"),
		A_DEFFLOAT,
		0);

	CLASS_MAINSIGNALIN(faustchorus_tilde_class, t_faustchorus_tilde, f);
	class_addmethod(faustchorus_tilde_class, (t_method)faustchorus_tilde_dsp, gensym("dsp"), A_CANT);

	class_addmethod(faustchorus_tilde_class, (t_method)faustchorus_instance_clear, gensym("clear"), 0);
}