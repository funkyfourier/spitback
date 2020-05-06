/* ------------------------------------------------------------
name: "faustdelay"
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
	float fVec0[524288];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHslider1;
	int fSampleRate;
	float fConst0;
	int iConst1;
	float fConst2;
	FAUSTFLOAT fHslider2;
	float fRec1[2];
	float fRec0[524288];
	float fVec1[524288];
	float fRec2[524288];
} mydsp;

mydsp* newmydsp() { 
	mydsp* dsp = (mydsp*)calloc(1, sizeof(mydsp));
	return dsp;
}

void deletemydsp(mydsp* dsp) { 
	free(dsp);
}

void metadatamydsp(MetaGlue* m) { 
	m->declare(m->metaInterface, "delays.lib/name", "Faust Delay Library");
	m->declare(m->metaInterface, "delays.lib/version", "0.1");
	m->declare(m->metaInterface, "filename", "faustdelay.dsp");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "faustdelay");
	m->declare(m->metaInterface, "signals.lib/name", "Faust Signal Routing Library");
	m->declare(m->metaInterface, "signals.lib/version", "0.0");
}

int getSampleRatemydsp(mydsp* dsp) {
	return dsp->fSampleRate;
}

int getNumInputsmydsp(mydsp* dsp) {
	return 2;
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 4;
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

void classInitmydsp(int sample_rate) {
}

void instanceResetUserInterfacemydsp(mydsp* dsp) {
	dsp->fHslider0 = (FAUSTFLOAT)1.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.69999999999999996f;
	dsp->fHslider2 = (FAUSTFLOAT)100.0f;
}

void instanceClearmydsp(mydsp* dsp) {
	dsp->IOTA = 0;
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 524288); l0 = (l0 + 1)) {
			dsp->fVec0[l0] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l1;
		for (l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			dsp->fRec1[l1] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l2;
		for (l2 = 0; (l2 < 524288); l2 = (l2 + 1)) {
			dsp->fRec0[l2] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 524288); l3 = (l3 + 1)) {
			dsp->fVec1[l3] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 524288); l4 = (l4 + 1)) {
			dsp->fRec2[l4] = 0.0f;
		}
	}
}

void instanceConstantsmydsp(mydsp* dsp, int sample_rate) {
	dsp->fSampleRate = sample_rate;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSampleRate));
	dsp->iConst1 = (int)(2.0f * dsp->fConst0);
	dsp->fConst2 = (0.00100000005f * dsp->fConst0);
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "faustdelay");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Delay", &dsp->fHslider2, 100.0f, 0.0f, 1000.0f, 1.0f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Feedback", &dsp->fHslider1, 0.699999988f, 0.0f, 0.899999976f, 0.00999999978f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "Wet", &dsp->fHslider0, 1.0f, 0.0f, 1.0f, 0.00999999978f);
	ui_interface->closeBox(ui_interface->uiInterface);
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* input1 = inputs[1];
	FAUSTFLOAT* output0 = outputs[0];
	FAUSTFLOAT* output1 = outputs[1];
	FAUSTFLOAT* output2 = outputs[2];
	FAUSTFLOAT* output3 = outputs[3];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = (float)dsp->fHslider1;
	float fSlow2 = (0.00100000005f * (float)dsp->fHslider2);
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float)input0[i];
			dsp->fVec0[(dsp->IOTA & 524287)] = fTemp0;
			output0[i] = (FAUSTFLOAT)fTemp0;
			dsp->fRec1[0] = (fSlow2 + (0.999000013f * dsp->fRec1[1]));
			int iTemp1 = (int)(dsp->fConst2 * dsp->fRec1[0]);
			int iTemp2 = min(dsp->iConst1, max(0, (2 * iTemp1)));
			int iTemp3 = (iTemp2 + 1);
			dsp->fRec0[(dsp->IOTA & 524287)] = (fSlow1 * (dsp->fRec0[((dsp->IOTA - iTemp3) & 524287)] + dsp->fVec0[((dsp->IOTA - min(dsp->iConst1, max(0, iTemp1))) & 524287)]));
			output1[i] = (FAUSTFLOAT)(fSlow0 * dsp->fRec0[((dsp->IOTA - 0) & 524287)]);
			float fTemp4 = (float)input1[i];
			dsp->fVec1[(dsp->IOTA & 524287)] = fTemp4;
			dsp->fRec2[(dsp->IOTA & 524287)] = (fSlow1 * (dsp->fRec2[((dsp->IOTA - iTemp3) & 524287)] + dsp->fVec1[((dsp->IOTA - iTemp2) & 524287)]));
			output2[i] = (FAUSTFLOAT)(fSlow0 * dsp->fRec2[((dsp->IOTA - 0) & 524287)]);
			output3[i] = (FAUSTFLOAT)fTemp4;
			dsp->IOTA = (dsp->IOTA + 1);
			dsp->fRec1[1] = dsp->fRec1[0];
		}
	}
}

#ifdef __cplusplus
}
#endif

#endif
