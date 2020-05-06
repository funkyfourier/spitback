/* ------------------------------------------------------------
name: "faustflange"
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
	
	FAUSTFLOAT fHslider0;
	int iVec0[2];
	int IOTA;
	float fVec1[8192];
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fConst1;
	FAUSTFLOAT fHslider2;
	float fRec1[2];
	float fRec2[2];
	float fRec0[2];
	float fVec2[8192];
	float fRec3[2];
	
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
	m->declare(m->metaInterface, "name", "faustflange");
	m->declare(m->metaInterface, "oscillators.lib/name", "Faust Oscillator Library");
	m->declare(m->metaInterface, "oscillators.lib/version", "0.0");
	m->declare(m->metaInterface, "phaflangers.lib/name", "Faust Phaser and Flanger Library");
	m->declare(m->metaInterface, "phaflangers.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) { return dsp->fSamplingFreq; }

int getNumInputsmydsp(mydsp* dsp) {
	return 2;
	
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 2;
	
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
	dsp->fHslider0 = (FAUSTFLOAT)0.0f;
	dsp->fHslider1 = (FAUSTFLOAT)10.0f;
	dsp->fHslider2 = (FAUSTFLOAT)0.5f;
	
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			dsp->iVec0[l0] = 0;
			
		}
		
	}
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 8192); l1 = (l1 + 1)) {
			dsp->fVec1[l1] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			dsp->fRec1[l2] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			dsp->fRec2[l3] = 0.0f;
			
		}
		
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			dsp->fRec0[l4] = 0.0f;
			
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
	
}

void instanceConstantsmydsp(mydsp* dsp, int samplingFreq) {
	dsp->fSamplingFreq = samplingFreq;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSamplingFreq));
	dsp->fConst1 = (6.28318548f / dsp->fConst0);
	
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "faustflange");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Feedback", &dsp->fHslider0, 0.0f, -0.999000013f, 0.999000013f, 0.00100000005f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Speed", &dsp->fHslider2, 0.5f, 0.0f, 10.0f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Width", &dsp->fHslider1, 10.0f, 0.0f, 20.0f, 0.00100000005f);
	ui_interface->closeBox(ui_interface->uiInterface);
	
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (dsp->fConst0 * (float)dsp->fHslider1);
	float fSlow2 = (dsp->fConst1 * (float)dsp->fHslider2);
	float fSlow3 = sinf(fSlow2);
	float fSlow4 = cosf(fSlow2);
	float fSlow5 = (0.0f - fSlow3);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			dsp->iVec0[0] = 1;
			float fTemp0 = (float)input0[i];
			float fTemp1 = ((fSlow0 * dsp->fRec0[1]) - fTemp0);
			dsp->fVec1[(dsp->IOTA & 8191)] = fTemp1;
			dsp->fRec1[0] = ((fSlow3 * dsp->fRec2[1]) + (fSlow4 * dsp->fRec1[1]));
			dsp->fRec2[0] = (((fSlow4 * dsp->fRec2[1]) + (fSlow5 * dsp->fRec1[1])) + (float)(1 - dsp->iVec0[1]));
			float fTemp2 = (fSlow1 * ((0.000500000024f * (dsp->fRec1[0] + 1.0f)) + 0.00100000005f));
			int iTemp3 = (int)fTemp2;
			float fTemp4 = floorf(fTemp2);
			dsp->fRec0[0] = ((dsp->fVec1[((dsp->IOTA - min(4097, max(0, iTemp3))) & 8191)] * (fTemp4 + (1.0f - fTemp2))) + ((fTemp2 - fTemp4) * dsp->fVec1[((dsp->IOTA - min(4097, max(0, (iTemp3 + 1)))) & 8191)]));
			output0[i] = (FAUSTFLOAT)(0.5f * (dsp->fRec0[0] + fTemp0));
			float fTemp5 = (float)input1[i];
			float fTemp6 = ((fSlow0 * dsp->fRec3[1]) - fTemp5);
			dsp->fVec2[(dsp->IOTA & 8191)] = fTemp6;
			float fTemp7 = (fSlow1 * ((0.000500000024f * (dsp->fRec2[0] + 1.0f)) + 0.00100000005f));
			int iTemp8 = (int)fTemp7;
			float fTemp9 = floorf(fTemp7);
			dsp->fRec3[0] = ((dsp->fVec2[((dsp->IOTA - min(4097, max(0, iTemp8))) & 8191)] * (fTemp9 + (1.0f - fTemp7))) + ((fTemp7 - fTemp9) * dsp->fVec2[((dsp->IOTA - min(4097, max(0, (iTemp8 + 1)))) & 8191)]));
			output1[i] = (FAUSTFLOAT)(0.5f * (dsp->fRec3[0] + fTemp5));
			dsp->iVec0[1] = dsp->iVec0[0];
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec1[1] = dsp->fRec1[0];
			dsp->fRec2[1] = dsp->fRec2[0];
			dsp->fRec0[1] = dsp->fRec0[0];
			dsp->fRec3[1] = dsp->fRec3[0];
			
		}
		
	}
	
}

#ifdef __cplusplus
}
#endif


#endif
