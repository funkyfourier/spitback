/* ------------------------------------------------------------
name: "faustrevstereo"
Code generated with Faust 2.20.2 (https://faust.grame.fr)
Compilation options: -lang c -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
#include <stdlib.h>


#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif
#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

typedef struct {
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
	FAUSTFLOAT fHslider0;
	float fConst6;
	FAUSTFLOAT fHslider1;
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
	FAUSTFLOAT fHslider2;
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
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)calloc(1, sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "basics.lib/name", "Faust Basic Element Library");
	m->declare(m->metaInterface, "basics.lib/version", "0.1");
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.1");
	m->declare(m->metaInterface, "filename", "faustrevstereo.dsp");
	m->declare(m->metaInterface, "filters.lib/allpass_comb:author", "Julius O. Smith III");
	m->declare(m->metaInterface, "filters.lib/allpass_comb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
	m->declare(m->metaInterface, "filters.lib/allpass_comb:license", "MIT-style STK-4.3 license");
	m->declare(m->metaInterface, "filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "faustrevstereo");
}

int getSampleRatemydsp(mydsp* dsp) {
	return dsp->fSampleRate;
}

int getNumInputsmydsp(mydsp* dsp) {
	return 2;
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch ((channel)) {
		case 0: {
			rate = 1;
			break;
		}
		case 1: {
			rate = 1;
			break;
		}
		default: {
			rate = -1;
			break;
		}
	}
	return rate;
}
int getOutputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch ((channel)) {
		case 0: {
			rate = 1;
			break;
		}
		case 1: {
			rate = 1;
			break;
		}
		default: {
			rate = -1;
			break;
		}
	}
	return rate;
}

void classInitmydsp(int sample_rate) {
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)0.5f;
	dsp->fHslider1 = (FAUSTFLOAT)0.5f;
	dsp->fHslider2 = (FAUSTFLOAT)0.5f;
}

void instanceClearmydsp(mydsp* dsp) {
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2048); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec7[l1] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2048); l2 = (l2 + 1)) {
			dsp->fVec1[l2] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec5[l3] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2048); l4 = (l4 + 1)) {
			dsp->fVec2[l4] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec3[l5] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 1024); l6 = (l6 + 1)) {
			dsp->fVec3[l6] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec1[l7] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec9[l8] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 4096); l9 = (l9 + 1)) {
			dsp->fVec4[l9] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec0[l10] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec11[l11] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 4096); l12 = (l12 + 1)) {
			dsp->fVec5[l12] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			dsp->fRec10[l13] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec13[l14] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 4096); l15 = (l15 + 1)) {
			dsp->fVec6[l15] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			dsp->fRec12[l16] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec15[l17] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 4096); l18 = (l18 + 1)) {
			dsp->fVec7[l18] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			dsp->fRec14[l19] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec17[l20] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 4096); l21 = (l21 + 1)) {
			dsp->fVec8[l21] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			dsp->fRec16[l22] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fRec19[l23] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 4096); l24 = (l24 + 1)) {
			dsp->fVec9[l24] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec18[l25] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			dsp->fRec21[l26] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 4096); l27 = (l27 + 1)) {
			dsp->fVec10[l27] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			dsp->fRec20[l28] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec23[l29] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 4096); l30 = (l30 + 1)) {
			dsp->fVec11[l30] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec22[l31] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec25[l32] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l33;
		for (l33 = 0; (l33 < 4096); l33 = (l33 + 1)) {
			dsp->fVec12[l33] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l34;
		for (l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			dsp->fRec24[l34] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fRec27[l35] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l36;
		for (l36 = 0; (l36 < 4096); l36 = (l36 + 1)) {
			dsp->fVec13[l36] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l37;
		for (l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			dsp->fRec26[l37] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec29[l38] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l39;
		for (l39 = 0; (l39 < 4096); l39 = (l39 + 1)) {
			dsp->fVec14[l39] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l40;
		for (l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			dsp->fRec28[l40] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec31[l41] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l42;
		for (l42 = 0; (l42 < 4096); l42 = (l42 + 1)) {
			dsp->fVec15[l42] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l43;
		for (l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			dsp->fRec30[l43] = 0.0f;
		}
	}
}

void instanceConstantsmydsp(mydsp* dsp, int sample_rate) {
	dsp->fSampleRate = sample_rate;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSampleRate));
	dsp->iConst1 = min(1024, max(0, ((int)(0.0126077095f * dsp->fConst0) + -1)));
	dsp->iConst2 = min(1024, max(0, ((int)(0.00999999978f * dsp->fConst0) + -1)));
	dsp->iConst3 = min(1024, max(0, ((int)(0.00773242628f * dsp->fConst0) + -1)));
	dsp->iConst4 = min(1024, max(0, ((int)(0.00510204071f * dsp->fConst0) + -1)));
	dsp->fConst5 = (6.34920616e-06f * dsp->fConst0);
	dsp->fConst6 = (1.92743755e-05f * dsp->fConst0);
	dsp->iConst7 = (int)(0.0253061224f * dsp->fConst0);
	dsp->iConst8 = min(2048, max(0, dsp->iConst7));
	dsp->iConst9 = (int)(0.0269387756f * dsp->fConst0);
	dsp->iConst10 = min(2048, max(0, dsp->iConst9));
	dsp->iConst11 = (int)(0.0289569162f * dsp->fConst0);
	dsp->iConst12 = min(2048, max(0, dsp->iConst11));
	dsp->iConst13 = (int)(0.0307482984f * dsp->fConst0);
	dsp->iConst14 = min(2048, max(0, dsp->iConst13));
	dsp->iConst15 = (int)(0.0322448984f * dsp->fConst0);
	dsp->iConst16 = min(2048, max(0, dsp->iConst15));
	dsp->iConst17 = (int)(0.033809524f * dsp->fConst0);
	dsp->iConst18 = min(2048, max(0, dsp->iConst17));
	dsp->fConst19 = (0.00104308384f * dsp->fConst0);
}

void instanceInitmydsp(mydsp* dsp, int sample_rate) {
	instanceConstantsmydsp(dsp, sample_rate);
	instanceResetUserInterfacemydsp(dsp);
	instanceClearmydsp(dsp);
}

void initmydsp(mydsp* dsp, int sample_rate) {
	classInitmydsp(sample_rate);
	instanceInitmydsp(dsp, sample_rate);
}

void buildUserInterfacemydsp(mydsp* dsp, UIGlue* ui_interface) {
	ui_interface->openVerticalBox(ui_interface->uiInterface, "faustrevstereo");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Damping", &dsp->fHslider1, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "RoomSize", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "SpatialSpread", &dsp->fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = ((dsp->fConst5 * (float)dsp->fHslider0) + 0.699999988f);
	float fSlow1 = (dsp->fConst6 * (float)dsp->fHslider1);
	float fSlow2 = (1.0f - fSlow1);
	int iSlow3 = (int)(dsp->fConst19 * (float)dsp->fHslider2);
	int iSlow4 = min(2048, max(0, (dsp->iConst7 + iSlow3)));
	int iSlow5 = min(2048, max(0, (dsp->iConst9 + iSlow3)));
	int iSlow6 = min(2048, max(0, (dsp->iConst11 + iSlow3)));
	int iSlow7 = min(2048, max(0, (dsp->iConst13 + iSlow3)));
	int iSlow8 = min(2048, max(0, (dsp->iConst15 + iSlow3)));
	int iSlow9 = min(2048, max(0, (dsp->iConst17 + iSlow3)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = ((0.5f * dsp->fRec7[1]) + (0.100000001f * ((float)input0[i] + (float)input1[i])));
			dsp->fVec0[(dsp->IOTA & 2047)] = fTemp0;
			dsp->fRec7[0] = dsp->fVec0[((dsp->IOTA - dsp->iConst1) & 2047)];
			float fRec8 = (0.0f - (0.5f * fTemp0));
			float fTemp1 = (dsp->fRec7[1] + (fRec8 + (0.5f * dsp->fRec5[1])));
			dsp->fVec1[(dsp->IOTA & 2047)] = fTemp1;
			dsp->fRec5[0] = dsp->fVec1[((dsp->IOTA - dsp->iConst2) & 2047)];
			float fRec6 = (0.0f - (0.5f * fTemp1));
			float fTemp2 = (dsp->fRec5[1] + (fRec6 + (0.5f * dsp->fRec3[1])));
			dsp->fVec2[(dsp->IOTA & 2047)] = fTemp2;
			dsp->fRec3[0] = dsp->fVec2[((dsp->IOTA - dsp->iConst3) & 2047)];
			float fRec4 = (0.0f - (0.5f * fTemp2));
			float fTemp3 = (dsp->fRec3[1] + (fRec4 + (0.5f * dsp->fRec1[1])));
			dsp->fVec3[(dsp->IOTA & 1023)] = fTemp3;
			dsp->fRec1[0] = dsp->fVec3[((dsp->IOTA - dsp->iConst4) & 1023)];
			float fRec2 = (0.0f - (0.5f * fTemp3));
			dsp->fRec9[0] = ((fSlow1 * dsp->fRec9[1]) + (fSlow2 * dsp->fRec0[1]));
			dsp->fVec4[(dsp->IOTA & 4095)] = (dsp->fRec1[1] + (fRec2 + (fSlow0 * dsp->fRec9[0])));
			dsp->fRec0[0] = dsp->fVec4[((dsp->IOTA - dsp->iConst8) & 4095)];
			float fTemp4 = (fRec2 + dsp->fRec1[1]);
			dsp->fRec11[0] = ((fSlow1 * dsp->fRec11[1]) + (fSlow2 * dsp->fRec10[1]));
			dsp->fVec5[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec11[0]));
			dsp->fRec10[0] = dsp->fVec5[((dsp->IOTA - dsp->iConst10) & 4095)];
			dsp->fRec13[0] = ((fSlow1 * dsp->fRec13[1]) + (fSlow2 * dsp->fRec12[1]));
			dsp->fVec6[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec13[0]));
			dsp->fRec12[0] = dsp->fVec6[((dsp->IOTA - dsp->iConst12) & 4095)];
			dsp->fRec15[0] = ((fSlow1 * dsp->fRec15[1]) + (fSlow2 * dsp->fRec14[1]));
			dsp->fVec7[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec15[0]));
			dsp->fRec14[0] = dsp->fVec7[((dsp->IOTA - dsp->iConst14) & 4095)];
			dsp->fRec17[0] = ((fSlow1 * dsp->fRec17[1]) + (fSlow2 * dsp->fRec16[1]));
			dsp->fVec8[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec17[0]));
			dsp->fRec16[0] = dsp->fVec8[((dsp->IOTA - dsp->iConst16) & 4095)];
			dsp->fRec19[0] = ((fSlow1 * dsp->fRec19[1]) + (fSlow2 * dsp->fRec18[1]));
			dsp->fVec9[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec19[0]));
			dsp->fRec18[0] = dsp->fVec9[((dsp->IOTA - dsp->iConst18) & 4095)];
			output0[i] = (FAUSTFLOAT)(((((dsp->fRec0[0] + dsp->fRec10[0]) + dsp->fRec12[0]) + dsp->fRec14[0]) + dsp->fRec16[0]) + dsp->fRec18[0]);
			dsp->fRec21[0] = ((fSlow1 * dsp->fRec21[1]) + (fSlow2 * dsp->fRec20[1]));
			dsp->fVec10[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec21[0]));
			dsp->fRec20[0] = dsp->fVec10[((dsp->IOTA - iSlow4) & 4095)];
			dsp->fRec23[0] = ((fSlow1 * dsp->fRec23[1]) + (fSlow2 * dsp->fRec22[1]));
			dsp->fVec11[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec23[0]));
			dsp->fRec22[0] = dsp->fVec11[((dsp->IOTA - iSlow5) & 4095)];
			dsp->fRec25[0] = ((fSlow1 * dsp->fRec25[1]) + (fSlow2 * dsp->fRec24[1]));
			dsp->fVec12[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec25[0]));
			dsp->fRec24[0] = dsp->fVec12[((dsp->IOTA - iSlow6) & 4095)];
			dsp->fRec27[0] = ((fSlow1 * dsp->fRec27[1]) + (fSlow2 * dsp->fRec26[1]));
			dsp->fVec13[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec27[0]));
			dsp->fRec26[0] = dsp->fVec13[((dsp->IOTA - iSlow7) & 4095)];
			dsp->fRec29[0] = ((fSlow1 * dsp->fRec29[1]) + (fSlow2 * dsp->fRec28[1]));
			dsp->fVec14[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec29[0]));
			dsp->fRec28[0] = dsp->fVec14[((dsp->IOTA - iSlow8) & 4095)];
			dsp->fRec31[0] = ((fSlow1 * dsp->fRec31[1]) + (fSlow2 * dsp->fRec30[1]));
			dsp->fVec15[(dsp->IOTA & 4095)] = (fTemp4 + (fSlow0 * dsp->fRec31[0]));
			dsp->fRec30[0] = dsp->fVec15[((dsp->IOTA - iSlow9) & 4095)];
			output1[i] = (FAUSTFLOAT)(((((dsp->fRec20[0] + dsp->fRec22[0]) + dsp->fRec24[0]) + dsp->fRec26[0]) + dsp->fRec28[0]) + dsp->fRec30[0]);
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec11[1] = dsp->fRec11[0];
			dsp->fRec10[1] = dsp->fRec10[0];
			dsp->fRec13[1] = dsp->fRec13[0];
			dsp->fRec12[1] = dsp->fRec12[0];
			dsp->fRec15[1] = dsp->fRec15[0];
			dsp->fRec14[1] = dsp->fRec14[0];
			dsp->fRec17[1] = dsp->fRec17[0];
			dsp->fRec16[1] = dsp->fRec16[0];
			dsp->fRec19[1] = dsp->fRec19[0];
			dsp->fRec18[1] = dsp->fRec18[0];
			dsp->fRec21[1] = dsp->fRec21[0];
			dsp->fRec20[1] = dsp->fRec20[0];
			dsp->fRec23[1] = dsp->fRec23[0];
			dsp->fRec22[1] = dsp->fRec22[0];
			dsp->fRec25[1] = dsp->fRec25[0];
			dsp->fRec24[1] = dsp->fRec24[0];
			dsp->fRec27[1] = dsp->fRec27[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec29[1] = dsp->fRec29[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec31[1] = dsp->fRec31[0];
			dsp->fRec30[1] = dsp->fRec30[0];
		}
	}
}

#ifdef __cplusplus
}
#endif

#endif
