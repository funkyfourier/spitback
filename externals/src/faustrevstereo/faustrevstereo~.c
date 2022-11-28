#include "m_pd.h"
#include "math.h"
#include <stdlib.h>

static t_class *faustrevstereo_tilde_class;

typedef struct _faustrevstereo_tilde
{

    t_object x_obj;
    t_float f;
    t_sample *in_l_buffer;
    t_sample *in_r_buffer;
    t_inlet *inlet_right;

    t_outlet *outlet_l;
    t_outlet *outlet_r;

    t_float room_size;
    t_float damping;
    t_float spread;

    int IOTA;
	float fVec0[2048];
	int fSampleRate;
	float fConst0;
	int iConst1;
	float fRec7[2];
	float fVec1[2048];
	int iConst2;
	float fRec5[2];
	float fVec2[2048];
	int iConst3;
	float fRec3[2];
	float fVec3[1024];
	int iConst4;
	float fRec1[2];
	float fConst5;
	float fConst6;
	float fRec9[2];
	float fVec4[4096];
	int iConst7;
	int iConst8;
	float fRec0[2];
	float fRec11[2];
	float fVec5[4096];
	int iConst9;
	int iConst10;
	float fRec10[2];
	float fRec13[2];
	float fVec6[4096];
	int iConst11;
	int iConst12;
	float fRec12[2];
	float fRec15[2];
	float fVec7[4096];
	int iConst13;
	int iConst14;
	float fRec14[2];
	float fRec17[2];
	float fVec8[4096];
	int iConst15;
	int iConst16;
	float fRec16[2];
	float fRec19[2];
	float fVec9[4096];
	int iConst17;
	int iConst18;
	float fRec18[2];
	float fRec21[2];
	float fVec10[4096];
	float fConst19;
	float fRec20[2];
	float fRec23[2];
	float fVec11[4096];
	float fRec22[2];
	float fRec25[2];
	float fVec12[4096];
	float fRec24[2];
	float fRec27[2];
	float fVec13[4096];
	float fRec26[2];
	float fRec29[2];
	float fVec14[4096];
	float fRec28[2];
	float fRec31[2];
	float fVec15[4096];
	float fRec30[2];
} t_faustrevstereo_tilde;

void faustrevstereo_instance_clear(t_faustrevstereo_tilde *this_object)
{
	this_object->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2048); l0 = (l0 + 1)) {
			this_object->fVec0[l0] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			this_object->fRec7[l1] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2048); l2 = (l2 + 1)) {
			this_object->fVec1[l2] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			this_object->fRec5[l3] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			this_object->fVec2[l4] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			this_object->fRec3[l5] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 1024); l6 = (l6 + 1)) {
			this_object->fVec3[l6] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			this_object->fRec1[l7] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			this_object->fRec9[l8] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 4096); l9 = (l9 + 1)) {
			this_object->fVec4[l9] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			this_object->fRec0[l10] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			this_object->fRec11[l11] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 4096); l12 = (l12 + 1)) {
			this_object->fVec5[l12] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			this_object->fRec10[l13] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			this_object->fRec13[l14] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 4096); l15 = (l15 + 1)) {
			this_object->fVec6[l15] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			this_object->fRec12[l16] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			this_object->fRec15[l17] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 4096); l18 = (l18 + 1)) {
			this_object->fVec7[l18] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			this_object->fRec14[l19] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			this_object->fRec17[l20] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 4096); l21 = (l21 + 1)) {
			this_object->fVec8[l21] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			this_object->fRec16[l22] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			this_object->fRec19[l23] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 4096); l24 = (l24 + 1)) {
			this_object->fVec9[l24] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			this_object->fRec18[l25] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			this_object->fRec21[l26] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 4096); l27 = (l27 + 1)) {
			this_object->fVec10[l27] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			this_object->fRec20[l28] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			this_object->fRec23[l29] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 4096); l30 = (l30 + 1)) {
			this_object->fVec11[l30] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			this_object->fRec22[l31] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			this_object->fRec25[l32] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 4096); l33 = (l33 + 1)) {
			this_object->fVec12[l33] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			this_object->fRec24[l34] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			this_object->fRec27[l35] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 4096); l36 = (l36 + 1)) {
			this_object->fVec13[l36] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			this_object->fRec26[l37] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			this_object->fRec29[l38] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 4096); l39 = (l39 + 1)) {
			this_object->fVec14[l39] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			this_object->fRec28[l40] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			this_object->fRec31[l41] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 4096); l42 = (l42 + 1)) {
			this_object->fVec15[l42] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			this_object->fRec30[l43] = 0.0f;
		}
	}
}

static int imax(int a, int b) { return a > b ? a : b; }

static int imin(int a, int b) { return a < b ? a : b; }

void *faustrevstereo_new(void)
{

    t_faustrevstereo_tilde *this_object = (t_faustrevstereo_tilde *)pd_new(faustrevstereo_tilde_class);
    
    this_object->inlet_right = inlet_new(&this_object->x_obj, &this_object->x_obj.ob_pd, &s_signal, &s_signal);
    floatinlet_new(&this_object->x_obj, &this_object->room_size);
    floatinlet_new(&this_object->x_obj, &this_object->damping);
    floatinlet_new(&this_object->x_obj, &this_object->spread);
    this_object->outlet_l = outlet_new(&this_object->x_obj, &s_signal);
    this_object->outlet_r = outlet_new(&this_object->x_obj, &s_signal);

    this_object->room_size = 0.5;
    this_object->damping = 0.5;
    this_object->spread = 0.5;

    this_object->fSampleRate = (int)sys_getsr();

	this_object->fConst0 = fmin(192000.0f, fmax(1.0f, (float)this_object->fSampleRate));
	this_object->iConst1 = imin(1024, imax(0, ((int)(0.0126077095f * this_object->fConst0) + -1)));
	this_object->iConst2 = imin(1024, imax(0, ((int)(0.00999999978f * this_object->fConst0) + -1)));
	this_object->iConst3 = imin(1024, imax(0, ((int)(0.00773242628f * this_object->fConst0) + -1)));
	this_object->iConst4 = imin(1024, imax(0, ((int)(0.00510204071f * this_object->fConst0) + -1)));
	this_object->fConst5 = (6.34920616e-06f * this_object->fConst0);
	this_object->fConst6 = (1.92743755e-05f * this_object->fConst0);
	this_object->iConst7 = (int)(0.0253061224f * this_object->fConst0);
	this_object->iConst8 = imin(2048, imax(0, this_object->iConst7));
	this_object->iConst9 = (int)(0.0269387756f * this_object->fConst0);
	this_object->iConst10 = imin(2048, imax(0, this_object->iConst9));
	this_object->iConst11 = (int)(0.0289569162f * this_object->fConst0);
	this_object->iConst12 = imin(2048, imax(0, this_object->iConst11));
	this_object->iConst13 = (int)(0.0307482984f * this_object->fConst0);
	this_object->iConst14 = imin(2048, imax(0, this_object->iConst13));
	this_object->iConst15 = (int)(0.0322448984f * this_object->fConst0);
	this_object->iConst16 = imin(2048, imax(0, this_object->iConst15));
	this_object->iConst17 = (int)(0.033809524f * this_object->fConst0);
	this_object->iConst18 = imin(2048, imax(0, this_object->iConst17));
	this_object->fConst19 = (0.00104308384f * this_object->fConst0);

    faustrevstereo_instance_clear(this_object);

    return (void *)this_object;
}

void faustrevstereo_tilde_free(t_faustrevstereo_tilde *this_object)
{
    free(this_object->in_l_buffer);
    free(this_object->in_r_buffer);
}

t_int *faustrevstereo_tilde_perform(t_int *w)
{
    t_faustrevstereo_tilde *this_object = (t_faustrevstereo_tilde *)(w[1]);
    t_sample *inL = (t_sample *)(w[2]); 
	t_sample *inR = (t_sample *)(w[3]); 
	t_sample *outL = (t_sample *)(w[4]);
	t_sample *outR = (t_sample *)(w[5]);  
    int n = (int)(w[6]);

    for (int i = 0; (i < n); i = (i + 1)) {
        this_object->in_l_buffer[i] = inL[i];
        this_object->in_r_buffer[i] = inR[i];
    }

	float fSlow0 = ((this_object->fConst5 * (float)this_object->room_size) + 0.699999988f);
	float fSlow1 = (this_object->fConst6 * (float)this_object->damping);
	float fSlow2 = (1.0f - fSlow1);
	int iSlow3 = (int)(this_object->fConst19 * (float)this_object->spread);
	int iSlow4 = imin(2048, imax(0, (this_object->iConst7 + iSlow3)));
	int iSlow5 = imin(2048, imax(0, (this_object->iConst9 + iSlow3)));
	int iSlow6 = imin(2048, imax(0, (this_object->iConst11 + iSlow3)));
	int iSlow7 = imin(2048, imax(0, (this_object->iConst13 + iSlow3)));
	int iSlow8 = imin(2048, imax(0, (this_object->iConst15 + iSlow3)));
	int iSlow9 = imin(2048, imax(0, (this_object->iConst17 + iSlow3)));


	/* C99 loop */
	{
		int i;
		for (i = 0; (i < n); i = (i + 1)) {
			float fTemp0 = ((0.5f * this_object->fRec7[1]) + (0.100000001f * ((float)this_object->in_l_buffer[i] + (float)this_object->in_r_buffer[i])));
			this_object->fVec0[(this_object->IOTA & 2047)] = fTemp0;
			this_object->fRec7[0] = this_object->fVec0[((this_object->IOTA - this_object->iConst1) & 2047)];
			float fRec8 = (0.0f - (0.5f * fTemp0));
			float fTemp1 = (this_object->fRec7[1] + (fRec8 + (0.5f * this_object->fRec5[1])));
			this_object->fVec1[(this_object->IOTA & 2047)] = fTemp1;
			this_object->fRec5[0] = this_object->fVec1[((this_object->IOTA - this_object->iConst2) & 2047)];
			float fRec6 = (0.0f - (0.5f * fTemp1));
			float fTemp2 = (this_object->fRec5[1] + (fRec6 + (0.5f * this_object->fRec3[1])));
			this_object->fVec2[(this_object->IOTA & 2047)] = fTemp2;
			this_object->fRec3[0] = this_object->fVec2[((this_object->IOTA - this_object->iConst3) & 2047)];
			float fRec4 = (0.0f - (0.5f * fTemp2));
			float fTemp3 = (this_object->fRec3[1] + (fRec4 + (0.5f * this_object->fRec1[1])));
			this_object->fVec3[(this_object->IOTA & 1023)] = fTemp3;
			this_object->fRec1[0] = this_object->fVec3[((this_object->IOTA - this_object->iConst4) & 1023)];
			float fRec2 = (0.0f - (0.5f * fTemp3));
			this_object->fRec9[0] = ((fSlow1 * this_object->fRec9[1]) + (fSlow2 * this_object->fRec0[1]));
			this_object->fVec4[(this_object->IOTA & 4095)] = (this_object->fRec1[1] + (fRec2 + (fSlow0 * this_object->fRec9[0])));
			this_object->fRec0[0] = this_object->fVec4[((this_object->IOTA - this_object->iConst8) & 4095)];
			float fTemp4 = (fRec2 + this_object->fRec1[1]);
			this_object->fRec11[0] = ((fSlow1 * this_object->fRec11[1]) + (fSlow2 * this_object->fRec10[1]));
			this_object->fVec5[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec11[0]));
			this_object->fRec10[0] = this_object->fVec5[((this_object->IOTA - this_object->iConst10) & 4095)];
			this_object->fRec13[0] = ((fSlow1 * this_object->fRec13[1]) + (fSlow2 * this_object->fRec12[1]));
			this_object->fVec6[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec13[0]));
			this_object->fRec12[0] = this_object->fVec6[((this_object->IOTA - this_object->iConst12) & 4095)];
			this_object->fRec15[0] = ((fSlow1 * this_object->fRec15[1]) + (fSlow2 * this_object->fRec14[1]));
			this_object->fVec7[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec15[0]));
			this_object->fRec14[0] = this_object->fVec7[((this_object->IOTA - this_object->iConst14) & 4095)];
			this_object->fRec17[0] = ((fSlow1 * this_object->fRec17[1]) + (fSlow2 * this_object->fRec16[1]));
			this_object->fVec8[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec17[0]));
			this_object->fRec16[0] = this_object->fVec8[((this_object->IOTA - this_object->iConst16) & 4095)];
			this_object->fRec19[0] = ((fSlow1 * this_object->fRec19[1]) + (fSlow2 * this_object->fRec18[1]));
			this_object->fVec9[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec19[0]));
			this_object->fRec18[0] = this_object->fVec9[((this_object->IOTA - this_object->iConst18) & 4095)];
			outL[i] = (t_sample)(((((this_object->fRec0[0] + this_object->fRec10[0]) + this_object->fRec12[0]) + this_object->fRec14[0]) + this_object->fRec16[0]) + this_object->fRec18[0]);
			this_object->fRec21[0] = ((fSlow1 * this_object->fRec21[1]) + (fSlow2 * this_object->fRec20[1]));
			this_object->fVec10[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec21[0]));
			this_object->fRec20[0] = this_object->fVec10[((this_object->IOTA - iSlow4) & 4095)];
			this_object->fRec23[0] = ((fSlow1 * this_object->fRec23[1]) + (fSlow2 * this_object->fRec22[1]));
			this_object->fVec11[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec23[0]));
			this_object->fRec22[0] = this_object->fVec11[((this_object->IOTA - iSlow5) & 4095)];
			this_object->fRec25[0] = ((fSlow1 * this_object->fRec25[1]) + (fSlow2 * this_object->fRec24[1]));
			this_object->fVec12[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec25[0]));
			this_object->fRec24[0] = this_object->fVec12[((this_object->IOTA - iSlow6) & 4095)];
			this_object->fRec27[0] = ((fSlow1 * this_object->fRec27[1]) + (fSlow2 * this_object->fRec26[1]));
			this_object->fVec13[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec27[0]));
			this_object->fRec26[0] = this_object->fVec13[((this_object->IOTA - iSlow7) & 4095)];
			this_object->fRec29[0] = ((fSlow1 * this_object->fRec29[1]) + (fSlow2 * this_object->fRec28[1]));
			this_object->fVec14[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec29[0]));
			this_object->fRec28[0] = this_object->fVec14[((this_object->IOTA - iSlow8) & 4095)];
			this_object->fRec31[0] = ((fSlow1 * this_object->fRec31[1]) + (fSlow2 * this_object->fRec30[1]));
			this_object->fVec15[(this_object->IOTA & 4095)] = (fTemp4 + (fSlow0 * this_object->fRec31[0]));
			this_object->fRec30[0] = this_object->fVec15[((this_object->IOTA - iSlow9) & 4095)];
			outR[i] = (t_sample)(((((this_object->fRec20[0] + this_object->fRec22[0]) + this_object->fRec24[0]) + this_object->fRec26[0]) + this_object->fRec28[0]) + this_object->fRec30[0]);
			this_object->IOTA = (this_object->IOTA + 1);
			this_object->fRec7[1] = this_object->fRec7[0];
			this_object->fRec5[1] = this_object->fRec5[0];
			this_object->fRec3[1] = this_object->fRec3[0];
			this_object->fRec1[1] = this_object->fRec1[0];
			this_object->fRec9[1] = this_object->fRec9[0];
			this_object->fRec0[1] = this_object->fRec0[0];
			this_object->fRec11[1] = this_object->fRec11[0];
			this_object->fRec10[1] = this_object->fRec10[0];
			this_object->fRec13[1] = this_object->fRec13[0];
			this_object->fRec12[1] = this_object->fRec12[0];
			this_object->fRec15[1] = this_object->fRec15[0];
			this_object->fRec14[1] = this_object->fRec14[0];
			this_object->fRec17[1] = this_object->fRec17[0];
			this_object->fRec16[1] = this_object->fRec16[0];
			this_object->fRec19[1] = this_object->fRec19[0];
			this_object->fRec18[1] = this_object->fRec18[0];
			this_object->fRec21[1] = this_object->fRec21[0];
			this_object->fRec20[1] = this_object->fRec20[0];
			this_object->fRec23[1] = this_object->fRec23[0];
			this_object->fRec22[1] = this_object->fRec22[0];
			this_object->fRec25[1] = this_object->fRec25[0];
			this_object->fRec24[1] = this_object->fRec24[0];
			this_object->fRec27[1] = this_object->fRec27[0];
			this_object->fRec26[1] = this_object->fRec26[0];
			this_object->fRec29[1] = this_object->fRec29[0];
			this_object->fRec28[1] = this_object->fRec28[0];
			this_object->fRec31[1] = this_object->fRec31[0];
			this_object->fRec30[1] = this_object->fRec30[0];
		}
	}

    return (w + 7);
}

void faustrevstereo_tilde_dsp(t_faustrevstereo_tilde *this_object, t_signal **sp)
{
    dsp_add(faustrevstereo_tilde_perform, 6, this_object, sp[0]->s_vec, sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);
    this_object->in_l_buffer = malloc(sp[0]->s_n * sizeof(t_sample));
    this_object->in_r_buffer = malloc(sp[0]->s_n * sizeof(t_sample));
}

void faustrevstereo_tilde_setup(void)
{

    faustrevstereo_tilde_class = class_new(
        gensym("faustrevstereo~"),
        (t_newmethod)faustrevstereo_new,
        (t_method)faustrevstereo_tilde_free,
        sizeof(t_faustrevstereo_tilde),
        CLASS_DEFAULT,
        0);

    CLASS_MAINSIGNALIN(faustrevstereo_tilde_class, t_faustrevstereo_tilde, f);
    class_addmethod(faustrevstereo_tilde_class, (t_method)faustrevstereo_tilde_dsp, gensym("dsp"), A_CANT);

    class_addmethod(faustrevstereo_tilde_class, (t_method)faustrevstereo_instance_clear, gensym("clear"), 0);
}