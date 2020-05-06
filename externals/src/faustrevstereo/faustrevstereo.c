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
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	FAUSTFLOAT fHslider1;
	float fRec9[2];
	int IOTA;
	float fVec0[4096];
	int iConst3;
	int iConst4;
	float fRec8[2];
	float fRec11[2];
	float fVec1[4096];
	int iConst5;
	int iConst6;
	float fRec10[2];
	float fRec13[2];
	float fVec2[4096];
	int iConst7;
	int iConst8;
	float fRec12[2];
	float fRec15[2];
	float fVec3[4096];
	int iConst9;
	int iConst10;
	float fRec14[2];
	float fRec17[2];
	float fVec4[4096];
	int iConst11;
	int iConst12;
	float fRec16[2];
	float fRec19[2];
	float fVec5[4096];
	int iConst13;
	int iConst14;
	float fRec18[2];
	float fRec21[2];
	float fVec6[4096];
	int iConst15;
	int iConst16;
	float fRec20[2];
	float fRec23[2];
	float fVec7[4096];
	int iConst17;
	int iConst18;
	float fRec22[2];
	float fVec8[2048];
	int iConst19;
	float fRec6[2];
	float fVec9[2048];
	int iConst20;
	float fRec4[2];
	float fVec10[2048];
	int iConst21;
	float fRec2[2];
	float fVec11[1024];
	int iConst22;
	float fRec0[2];
	float fRec33[2];
	float fVec12[4096];
	float fConst23;
	FAUSTFLOAT fHslider2;
	float fRec32[2];
	float fRec35[2];
	float fVec13[4096];
	float fRec34[2];
	float fRec37[2];
	float fVec14[4096];
	float fRec36[2];
	float fRec39[2];
	float fVec15[4096];
	float fRec38[2];
	float fRec41[2];
	float fVec16[4096];
	float fRec40[2];
	float fRec43[2];
	float fVec17[4096];
	float fRec42[2];
	float fRec45[2];
	float fVec18[4096];
	float fRec44[2];
	float fRec47[2];
	float fVec19[4096];
	float fRec46[2];
	float fVec20[2048];
	float fRec30[2];
	float fVec21[2048];
	float fRec28[2];
	float fVec22[2048];
	float fRec26[2];
	float fVec23[1024];
	float fRec24[2];
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
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->fRec9[l0] = 0.0f;
		}
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 4096); l1 = (l1 + 1)) {
			dsp->fVec0[l1] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec8[l2] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec11[l3] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 4096); l4 = (l4 + 1)) {
			dsp->fVec1[l4] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			dsp->fRec10[l5] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec13[l6] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 4096); l7 = (l7 + 1)) {
			dsp->fVec2[l7] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec12[l8] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec15[l9] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 4096); l10 = (l10 + 1)) {
			dsp->fVec3[l10] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec14[l11] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l12;
		for (l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			dsp->fRec17[l12] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l13;
		for (l13 = 0; (l13 < 4096); l13 = (l13 + 1)) {
			dsp->fVec4[l13] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l14;
		for (l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			dsp->fRec16[l14] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l15;
		for (l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			dsp->fRec19[l15] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l16;
		for (l16 = 0; (l16 < 4096); l16 = (l16 + 1)) {
			dsp->fVec5[l16] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l17;
		for (l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			dsp->fRec18[l17] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l18;
		for (l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			dsp->fRec21[l18] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l19;
		for (l19 = 0; (l19 < 4096); l19 = (l19 + 1)) {
			dsp->fVec6[l19] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l20;
		for (l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			dsp->fRec20[l20] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l21;
		for (l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			dsp->fRec23[l21] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l22;
		for (l22 = 0; (l22 < 4096); l22 = (l22 + 1)) {
			dsp->fVec7[l22] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l23;
		for (l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			dsp->fRec22[l23] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l24;
		for (l24 = 0; (l24 < 2048); l24 = (l24 + 1)) {
			dsp->fVec8[l24] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l25;
		for (l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			dsp->fRec6[l25] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l26;
		for (l26 = 0; (l26 < 2048); l26 = (l26 + 1)) {
			dsp->fVec9[l26] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l27;
		for (l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			dsp->fRec4[l27] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l28;
		for (l28 = 0; (l28 < 2048); l28 = (l28 + 1)) {
			dsp->fVec10[l28] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l29;
		for (l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			dsp->fRec2[l29] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l30;
		for (l30 = 0; (l30 < 1024); l30 = (l30 + 1)) {
			dsp->fVec11[l30] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l31;
		for (l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			dsp->fRec0[l31] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l32;
		for (l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			dsp->fRec33[l32] = 0.0f;
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
			dsp->fRec32[l34] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l35;
		for (l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			dsp->fRec35[l35] = 0.0f;
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
			dsp->fRec34[l37] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l38;
		for (l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			dsp->fRec37[l38] = 0.0f;
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
			dsp->fRec36[l40] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l41;
		for (l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			dsp->fRec39[l41] = 0.0f;
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
			dsp->fRec38[l43] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l44;
		for (l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			dsp->fRec41[l44] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l45;
		for (l45 = 0; (l45 < 4096); l45 = (l45 + 1)) {
			dsp->fVec16[l45] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l46;
		for (l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			dsp->fRec40[l46] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l47;
		for (l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			dsp->fRec43[l47] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l48;
		for (l48 = 0; (l48 < 4096); l48 = (l48 + 1)) {
			dsp->fVec17[l48] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l49;
		for (l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			dsp->fRec42[l49] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l50;
		for (l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			dsp->fRec45[l50] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l51;
		for (l51 = 0; (l51 < 4096); l51 = (l51 + 1)) {
			dsp->fVec18[l51] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l52;
		for (l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			dsp->fRec44[l52] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l53;
		for (l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			dsp->fRec47[l53] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l54;
		for (l54 = 0; (l54 < 4096); l54 = (l54 + 1)) {
			dsp->fVec19[l54] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l55;
		for (l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			dsp->fRec46[l55] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l56;
		for (l56 = 0; (l56 < 2048); l56 = (l56 + 1)) {
			dsp->fVec20[l56] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l57;
		for (l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			dsp->fRec30[l57] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l58;
		for (l58 = 0; (l58 < 2048); l58 = (l58 + 1)) {
			dsp->fVec21[l58] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l59;
		for (l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			dsp->fRec28[l59] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l60;
		for (l60 = 0; (l60 < 2048); l60 = (l60 + 1)) {
			dsp->fVec22[l60] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l61;
		for (l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			dsp->fRec26[l61] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l62;
		for (l62 = 0; (l62 < 1024); l62 = (l62 + 1)) {
			dsp->fVec23[l62] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l63;
		for (l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			dsp->fRec24[l63] = 0.0f;
		}
	}
}

void instanceConstantsmydsp(mydsp* dsp, int sample_rate) {
	dsp->fSampleRate = sample_rate;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSampleRate));
	dsp->fConst1 = (6.34920616e-06f * dsp->fConst0);
	dsp->fConst2 = (1.92743755e-05f * dsp->fConst0);
	dsp->iConst3 = (int)(0.0253061224f * dsp->fConst0);
	dsp->iConst4 = min(2048, max(0, dsp->iConst3));
	dsp->iConst5 = (int)(0.0269387756f * dsp->fConst0);
	dsp->iConst6 = min(2048, max(0, dsp->iConst5));
	dsp->iConst7 = (int)(0.0289569162f * dsp->fConst0);
	dsp->iConst8 = min(2048, max(0, dsp->iConst7));
	dsp->iConst9 = (int)(0.0307482984f * dsp->fConst0);
	dsp->iConst10 = min(2048, max(0, dsp->iConst9));
	dsp->iConst11 = (int)(0.0322448984f * dsp->fConst0);
	dsp->iConst12 = min(2048, max(0, dsp->iConst11));
	dsp->iConst13 = (int)(0.033809524f * dsp->fConst0);
	dsp->iConst14 = min(2048, max(0, dsp->iConst13));
	dsp->iConst15 = (int)(0.0353061222f * dsp->fConst0);
	dsp->iConst16 = min(2048, max(0, dsp->iConst15));
	dsp->iConst17 = (int)(0.0366666652f * dsp->fConst0);
	dsp->iConst18 = min(2048, max(0, dsp->iConst17));
	dsp->iConst19 = min(1024, max(0, ((int)(0.0126077095f * dsp->fConst0) + -1)));
	dsp->iConst20 = min(1024, max(0, ((int)(0.00999999978f * dsp->fConst0) + -1)));
	dsp->iConst21 = min(1024, max(0, ((int)(0.00773242628f * dsp->fConst0) + -1)));
	dsp->iConst22 = min(1024, max(0, ((int)(0.00510204071f * dsp->fConst0) + -1)));
	dsp->fConst23 = (0.00104308384f * dsp->fConst0);
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
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Spatial Spread", &dsp->fHslider2, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = ((dsp->fConst1 * (float)dsp->fHslider0) + 0.699999988f);
	float fSlow1 = (dsp->fConst2 * (float)dsp->fHslider1);
	float fSlow2 = (1.0f - fSlow1);
	int iSlow3 = (int)(dsp->fConst23 * (float)dsp->fHslider2);
	int iSlow4 = min(2048, max(0, (dsp->iConst3 + iSlow3)));
	int iSlow5 = min(2048, max(0, (dsp->iConst5 + iSlow3)));
	int iSlow6 = min(2048, max(0, (dsp->iConst7 + iSlow3)));
	int iSlow7 = min(2048, max(0, (dsp->iConst9 + iSlow3)));
	int iSlow8 = min(2048, max(0, (dsp->iConst11 + iSlow3)));
	int iSlow9 = min(2048, max(0, (dsp->iConst13 + iSlow3)));
	int iSlow10 = min(2048, max(0, (dsp->iConst15 + iSlow3)));
	int iSlow11 = min(2048, max(0, (dsp->iConst17 + iSlow3)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->fRec9[0] = ((fSlow1 * dsp->fRec9[1]) + (fSlow2 * dsp->fRec8[1]));
			float fTemp0 = (0.100000001f * ((float)input0[i] + (float)input1[i]));
			dsp->fVec0[(dsp->IOTA & 4095)] = ((fSlow0 * dsp->fRec9[0]) + fTemp0);
			dsp->fRec8[0] = dsp->fVec0[((dsp->IOTA - dsp->iConst4) & 4095)];
			dsp->fRec11[0] = ((fSlow1 * dsp->fRec11[1]) + (fSlow2 * dsp->fRec10[1]));
			dsp->fVec1[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec11[0]));
			dsp->fRec10[0] = dsp->fVec1[((dsp->IOTA - dsp->iConst6) & 4095)];
			dsp->fRec13[0] = ((fSlow1 * dsp->fRec13[1]) + (fSlow2 * dsp->fRec12[1]));
			dsp->fVec2[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec13[0]));
			dsp->fRec12[0] = dsp->fVec2[((dsp->IOTA - dsp->iConst8) & 4095)];
			dsp->fRec15[0] = ((fSlow1 * dsp->fRec15[1]) + (fSlow2 * dsp->fRec14[1]));
			dsp->fVec3[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec15[0]));
			dsp->fRec14[0] = dsp->fVec3[((dsp->IOTA - dsp->iConst10) & 4095)];
			dsp->fRec17[0] = ((fSlow1 * dsp->fRec17[1]) + (fSlow2 * dsp->fRec16[1]));
			dsp->fVec4[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec17[0]));
			dsp->fRec16[0] = dsp->fVec4[((dsp->IOTA - dsp->iConst12) & 4095)];
			dsp->fRec19[0] = ((fSlow1 * dsp->fRec19[1]) + (fSlow2 * dsp->fRec18[1]));
			dsp->fVec5[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec19[0]));
			dsp->fRec18[0] = dsp->fVec5[((dsp->IOTA - dsp->iConst14) & 4095)];
			dsp->fRec21[0] = ((fSlow1 * dsp->fRec21[1]) + (fSlow2 * dsp->fRec20[1]));
			dsp->fVec6[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec21[0]));
			dsp->fRec20[0] = dsp->fVec6[((dsp->IOTA - dsp->iConst16) & 4095)];
			dsp->fRec23[0] = ((fSlow1 * dsp->fRec23[1]) + (fSlow2 * dsp->fRec22[1]));
			dsp->fVec7[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec23[0]));
			dsp->fRec22[0] = dsp->fVec7[((dsp->IOTA - dsp->iConst18) & 4095)];
			float fTemp1 = ((((((((dsp->fRec8[0] + dsp->fRec10[0]) + dsp->fRec12[0]) + dsp->fRec14[0]) + dsp->fRec16[0]) + dsp->fRec18[0]) + dsp->fRec20[0]) + dsp->fRec22[0]) + (0.5f * dsp->fRec6[1]));
			dsp->fVec8[(dsp->IOTA & 2047)] = fTemp1;
			dsp->fRec6[0] = dsp->fVec8[((dsp->IOTA - dsp->iConst19) & 2047)];
			float fRec7 = (0.0f - (0.5f * fTemp1));
			float fTemp2 = (dsp->fRec6[1] + (fRec7 + (0.5f * dsp->fRec4[1])));
			dsp->fVec9[(dsp->IOTA & 2047)] = fTemp2;
			dsp->fRec4[0] = dsp->fVec9[((dsp->IOTA - dsp->iConst20) & 2047)];
			float fRec5 = (0.0f - (0.5f * fTemp2));
			float fTemp3 = (dsp->fRec4[1] + (fRec5 + (0.5f * dsp->fRec2[1])));
			dsp->fVec10[(dsp->IOTA & 2047)] = fTemp3;
			dsp->fRec2[0] = dsp->fVec10[((dsp->IOTA - dsp->iConst21) & 2047)];
			float fRec3 = (0.0f - (0.5f * fTemp3));
			float fTemp4 = (dsp->fRec2[1] + (fRec3 + (0.5f * dsp->fRec0[1])));
			dsp->fVec11[(dsp->IOTA & 1023)] = fTemp4;
			dsp->fRec0[0] = dsp->fVec11[((dsp->IOTA - dsp->iConst22) & 1023)];
			float fRec1 = (0.0f - (0.5f * fTemp4));
			output0[i] = (FAUSTFLOAT)(fRec1 + dsp->fRec0[1]);
			dsp->fRec33[0] = ((fSlow1 * dsp->fRec33[1]) + (fSlow2 * dsp->fRec32[1]));
			dsp->fVec12[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec33[0]));
			dsp->fRec32[0] = dsp->fVec12[((dsp->IOTA - iSlow4) & 4095)];
			dsp->fRec35[0] = ((fSlow1 * dsp->fRec35[1]) + (fSlow2 * dsp->fRec34[1]));
			dsp->fVec13[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec35[0]));
			dsp->fRec34[0] = dsp->fVec13[((dsp->IOTA - iSlow5) & 4095)];
			dsp->fRec37[0] = ((fSlow1 * dsp->fRec37[1]) + (fSlow2 * dsp->fRec36[1]));
			dsp->fVec14[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec37[0]));
			dsp->fRec36[0] = dsp->fVec14[((dsp->IOTA - iSlow6) & 4095)];
			dsp->fRec39[0] = ((fSlow1 * dsp->fRec39[1]) + (fSlow2 * dsp->fRec38[1]));
			dsp->fVec15[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec39[0]));
			dsp->fRec38[0] = dsp->fVec15[((dsp->IOTA - iSlow7) & 4095)];
			dsp->fRec41[0] = ((fSlow1 * dsp->fRec41[1]) + (fSlow2 * dsp->fRec40[1]));
			dsp->fVec16[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec41[0]));
			dsp->fRec40[0] = dsp->fVec16[((dsp->IOTA - iSlow8) & 4095)];
			dsp->fRec43[0] = ((fSlow1 * dsp->fRec43[1]) + (fSlow2 * dsp->fRec42[1]));
			dsp->fVec17[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec43[0]));
			dsp->fRec42[0] = dsp->fVec17[((dsp->IOTA - iSlow9) & 4095)];
			dsp->fRec45[0] = ((fSlow1 * dsp->fRec45[1]) + (fSlow2 * dsp->fRec44[1]));
			dsp->fVec18[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec45[0]));
			dsp->fRec44[0] = dsp->fVec18[((dsp->IOTA - iSlow10) & 4095)];
			dsp->fRec47[0] = ((fSlow1 * dsp->fRec47[1]) + (fSlow2 * dsp->fRec46[1]));
			dsp->fVec19[(dsp->IOTA & 4095)] = (fTemp0 + (fSlow0 * dsp->fRec47[0]));
			dsp->fRec46[0] = dsp->fVec19[((dsp->IOTA - iSlow11) & 4095)];
			float fTemp5 = ((((((((dsp->fRec32[0] + dsp->fRec34[0]) + dsp->fRec36[0]) + dsp->fRec38[0]) + dsp->fRec40[0]) + dsp->fRec42[0]) + dsp->fRec44[0]) + dsp->fRec46[0]) + (0.5f * dsp->fRec30[1]));
			dsp->fVec20[(dsp->IOTA & 2047)] = fTemp5;
			dsp->fRec30[0] = dsp->fVec20[((dsp->IOTA - dsp->iConst19) & 2047)];
			float fRec31 = (0.0f - (0.5f * fTemp5));
			float fTemp6 = (dsp->fRec30[1] + (fRec31 + (0.5f * dsp->fRec28[1])));
			dsp->fVec21[(dsp->IOTA & 2047)] = fTemp6;
			dsp->fRec28[0] = dsp->fVec21[((dsp->IOTA - dsp->iConst20) & 2047)];
			float fRec29 = (0.0f - (0.5f * fTemp6));
			float fTemp7 = (dsp->fRec28[1] + (fRec29 + (0.5f * dsp->fRec26[1])));
			dsp->fVec22[(dsp->IOTA & 2047)] = fTemp7;
			dsp->fRec26[0] = dsp->fVec22[((dsp->IOTA - dsp->iConst21) & 2047)];
			float fRec27 = (0.0f - (0.5f * fTemp7));
			float fTemp8 = (dsp->fRec26[1] + (fRec27 + (0.5f * dsp->fRec24[1])));
			dsp->fVec23[(dsp->IOTA & 1023)] = fTemp8;
			dsp->fRec24[0] = dsp->fVec23[((dsp->IOTA - dsp->iConst22) & 1023)];
			float fRec25 = (0.0f - (0.5f * fTemp8));
			output1[i] = (FAUSTFLOAT)(fRec25 + dsp->fRec24[1]);
			dsp->fRec9[1] = dsp->fRec9[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec8[1] = dsp->fRec8[0];
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
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec33[1] = dsp->fRec33[0];
			dsp->fRec32[1] = dsp->fRec32[0];
			dsp->fRec35[1] = dsp->fRec35[0];
			dsp->fRec34[1] = dsp->fRec34[0];
			dsp->fRec37[1] = dsp->fRec37[0];
			dsp->fRec36[1] = dsp->fRec36[0];
			dsp->fRec39[1] = dsp->fRec39[0];
			dsp->fRec38[1] = dsp->fRec38[0];
			dsp->fRec41[1] = dsp->fRec41[0];
			dsp->fRec40[1] = dsp->fRec40[0];
			dsp->fRec43[1] = dsp->fRec43[0];
			dsp->fRec42[1] = dsp->fRec42[0];
			dsp->fRec45[1] = dsp->fRec45[0];
			dsp->fRec44[1] = dsp->fRec44[0];
			dsp->fRec47[1] = dsp->fRec47[0];
			dsp->fRec46[1] = dsp->fRec46[0];
			dsp->fRec30[1] = dsp->fRec30[0];
			dsp->fRec28[1] = dsp->fRec28[0];
			dsp->fRec26[1] = dsp->fRec26[0];
			dsp->fRec24[1] = dsp->fRec24[0];
		}
	}
}

#ifdef __cplusplus
}
#endif

#endif
