/* ------------------------------------------------------------
name: "faustchorus"
Code generated with Faust 2.5.12 (https://faust.grame.fr)
Compilation options: c, -scal -ftz 0
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
	float fVec0[8192];
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	int iVec1[2];
	float fRec0[2];
	float fConst2;
	FAUSTFLOAT fHslider1;
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
	
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)malloc(sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.0");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/version", "0.0");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "faustchorus");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 4;
	
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch (channel) {
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
	switch (channel) {
		case 0: {
			rate = 1;
			break;
		}
		case 1: {
			rate = 1;
			break;
		}
		case 2: {
			rate = 1;
			break;
		}
		case 3: {
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

void classInitmydsp(int samplingFreq) {
	
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)0.5f;
	dsp->fHslider1 = (FAUSTFLOAT)1.0f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 8192); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->iVec1[l1] = 0;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec0[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec1[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec2[l4] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l5;
		for (l5 = 0; (l5 < 8192); l5 = (l5 + 1)) {
			dsp->fVec2[l5] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l6;
		for (l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			dsp->fRec3[l6] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l7;
		for (l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			dsp->fRec4[l7] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l8;
		for (l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			dsp->fRec5[l8] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l9;
		for (l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			dsp->fRec6[l9] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l10;
		for (l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			dsp->fRec7[l10] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l11;
		for (l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			dsp->fRec8[l11] = 0.0f;
			
		}
		
	}
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (0.00100000005f * (float)(int)(0.0116099771f * dsp->fConst0));
	dsp->fConst2 = (6.28318548f / dsp->fConst0);
	dsp->fConst3 = (3.14159274f / dsp->fConst0);
	dsp->fConst4 = (2.09439516f / dsp->fConst0);
	dsp->fConst5 = (1.57079637f / dsp->fConst0);
	
}

void instanceInitmydsp(mydsp* dsp, int samplingFreq) {
	instanceConstantsmydsp(dsp, samplingFreq);
	instanceResetUserInterfacemydsp(dsp);
	instanceClearmydsp(dsp);
}

void initmydsp(mydsp* dsp, int samplingFreq) {
	classInitmydsp(samplingFreq);
	instanceInitmydsp(dsp, samplingFreq);
}

void buildUserInterfacemydsp(mydsp* dsp, UIGlue* ui_interface) {
	ui_interface->openVerticalBox(ui_interface->uiInterface, "faustchorus");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Depth", &dsp->fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Frequency", &dsp->fHslider1, 1.0f, 0.0f, 10.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	FAUSTFLOAT* output2 = outputs[2];
	FAUSTFLOAT* output3 = outputs[3];
	float fSlow0 = (dsp->fConst1 * (float)dsp->fHslider0);
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = (dsp->fConst2 * fSlow1);
	float fSlow3 = sinf(fSlow2);
	float fSlow4 = cosf(fSlow2);
	float fSlow5 = (0.0f - fSlow3);
	float fSlow6 = (dsp->fConst3 * fSlow1);
	float fSlow7 = sinf(fSlow6);
	float fSlow8 = cosf(fSlow6);
	float fSlow9 = (0.0f - fSlow7);
	float fSlow10 = (dsp->fConst4 * fSlow1);
	float fSlow11 = sinf(fSlow10);
	float fSlow12 = cosf(fSlow10);
	float fSlow13 = (0.0f - fSlow11);
	float fSlow14 = (dsp->fConst5 * fSlow1);
	float fSlow15 = sinf(fSlow14);
	float fSlow16 = cosf(fSlow14);
	float fSlow17 = (0.0f - fSlow15);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fVec0[(dsp->IOTA & 8191)] = fTemp0;
			dsp->iVec1[0] = 1;
			dsp->fRec0[0] = (fSlow0 + (0.999000013f * dsp->fRec0[1]));
			dsp->fRec1[0] = ((fSlow3 * dsp->fRec2[1]) + (fSlow4 * dsp->fRec1[1]));
			int iTemp1 = (1 - dsp->iVec1[1]);
			dsp->fRec2[0] = (((fSlow4 * dsp->fRec2[1]) + (fSlow5 * dsp->fRec1[1])) + (float)iTemp1);
			float fTemp2 = (dsp->fRec0[0] * (dsp->fRec1[0] + 1.0f));
			int iTemp3 = (int)fTemp2;
			float fTemp4 = floorf(fTemp2);
			output0[i] = (FAUSTFLOAT)((dsp->fVec0[((dsp->IOTA - min(4097, max(0, iTemp3))) & 8191)] * (fTemp4 + (1.0f - fTemp2))) + ((fTemp2 - fTemp4) * dsp->fVec0[((dsp->IOTA - min(4097, max(0, (iTemp3 + 1)))) & 8191)]));
			float fTemp5 = (float)input1[i];
			dsp->fVec2[(dsp->IOTA & 8191)] = fTemp5;
			dsp->fRec3[0] = ((fSlow7 * dsp->fRec4[1]) + (fSlow8 * dsp->fRec3[1]));
			dsp->fRec4[0] = (((fSlow8 * dsp->fRec4[1]) + (fSlow9 * dsp->fRec3[1])) + (float)iTemp1);
			float fTemp6 = (dsp->fRec0[0] * (dsp->fRec3[0] + 1.0f));
			int iTemp7 = (int)fTemp6;
			float fTemp8 = floorf(fTemp6);
			output1[i] = (FAUSTFLOAT)((dsp->fVec2[((dsp->IOTA - min(4097, max(0, iTemp7))) & 8191)] * (fTemp8 + (1.0f - fTemp6))) + ((fTemp6 - fTemp8) * dsp->fVec2[((dsp->IOTA - min(4097, max(0, (iTemp7 + 1)))) & 8191)]));
			dsp->fRec5[0] = ((fSlow11 * dsp->fRec6[1]) + (fSlow12 * dsp->fRec5[1]));
			dsp->fRec6[0] = (((fSlow12 * dsp->fRec6[1]) + (fSlow13 * dsp->fRec5[1])) + (float)iTemp1);
			float fTemp9 = (dsp->fRec0[0] * (dsp->fRec5[0] + 1.0f));
			int iTemp10 = (int)fTemp9;
			float fTemp11 = floorf(fTemp9);
			output2[i] = (FAUSTFLOAT)((dsp->fVec0[((dsp->IOTA - min(4097, max(0, iTemp10))) & 8191)] * (fTemp11 + (1.0f - fTemp9))) + ((fTemp9 - fTemp11) * dsp->fVec0[((dsp->IOTA - min(4097, max(0, (iTemp10 + 1)))) & 8191)]));
			dsp->fRec7[0] = ((fSlow15 * dsp->fRec8[1]) + (fSlow16 * dsp->fRec7[1]));
			dsp->fRec8[0] = (((fSlow16 * dsp->fRec8[1]) + (fSlow17 * dsp->fRec7[1])) + (float)iTemp1);
			float fTemp12 = (dsp->fRec0[0] * (dsp->fRec7[0] + 1.0f));
			int iTemp13 = (int)fTemp12;
			float fTemp14 = floorf(fTemp12);
			output3[i] = (FAUSTFLOAT)((dsp->fVec2[((dsp->IOTA - min(4097, max(0, iTemp13))) & 8191)] * (fTemp14 + (1.0f - fTemp12))) + ((fTemp12 - fTemp14) * dsp->fVec2[((dsp->IOTA - min(4097, max(0, (iTemp13 + 1)))) & 8191)]));
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->iVec1[1] = dsp->iVec1[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			dsp->fRec4[1] = dsp->fRec4[0];
			dsp->fRec5[1] = dsp->fRec5[0];
			dsp->fRec6[1] = dsp->fRec6[0];
			dsp->fRec7[1] = dsp->fRec7[0];
			dsp->fRec8[1] = dsp->fRec8[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
