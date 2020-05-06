/* ------------------------------------------------------------
name: "faustpeakeq"
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

static float mydsp_faustpower2_f(float value) {
	return (value * value);
}

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
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fConst2;
	float fRec0[3];
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
	m->declare(m->metaInterface, "filename", "faustpeakeq.dsp");
	m->declare(m->metaInterface, "filters.lib/fir:author", "Julius O. Smith III");
	m->declare(m->metaInterface, "filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
	m->declare(m->metaInterface, "filters.lib/fir:license", "MIT-style STK-4.3 license");
	m->declare(m->metaInterface, "filters.lib/iir:author", "Julius O. Smith III");
	m->declare(m->metaInterface, "filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
	m->declare(m->metaInterface, "filters.lib/iir:license", "MIT-style STK-4.3 license");
	m->declare(m->metaInterface, "filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
	m->declare(m->metaInterface, "filters.lib/name", "Faust Filters Library");
	m->declare(m->metaInterface, "filters.lib/peak_eq:author", "Julius O. Smith III");
	m->declare(m->metaInterface, "filters.lib/peak_eq:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
	m->declare(m->metaInterface, "filters.lib/peak_eq:license", "MIT-style STK-4.3 license");
	m->declare(m->metaInterface, "filters.lib/tf2:author", "Julius O. Smith III");
	m->declare(m->metaInterface, "filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
	m->declare(m->metaInterface, "filters.lib/tf2:license", "MIT-style STK-4.3 license");
	m->declare(m->metaInterface, "filters.lib/tf2s:author", "Julius O. Smith III");
	m->declare(m->metaInterface, "filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
	m->declare(m->metaInterface, "filters.lib/tf2s:license", "MIT-style STK-4.3 license");
	m->declare(m->metaInterface, "maths.lib/author", "GRAME");
	m->declare(m->metaInterface, "maths.lib/copyright", "GRAME");
	m->declare(m->metaInterface, "maths.lib/license", "LGPL with exception");
	m->declare(m->metaInterface, "maths.lib/name", "Faust Math Library");
	m->declare(m->metaInterface, "maths.lib/version", "2.1");
	m->declare(m->metaInterface, "name", "faustpeakeq");
}

int getSampleRatemydsp(mydsp* dsp) {
	return dsp->fSampleRate;
}

int getNumInputsmydsp(mydsp* dsp) {
	return 1;
}
int getNumOutputsmydsp(mydsp* dsp) {
	return 1;
}
int getInputRatemydsp(mydsp* dsp, int channel) {
	int rate;
	switch ((channel)) {
		case 0: {
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
	dsp->fHslider0 = (FAUSTFLOAT)2200.0f;
	dsp->fHslider1 = (FAUSTFLOAT)0.0f;
	dsp->fHslider2 = (FAUSTFLOAT)50.0f;
}

void instanceClearmydsp(mydsp* dsp) {
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			dsp->fRec0[l0] = 0.0f;
		}
	}
}

void instanceConstantsmydsp(mydsp* dsp, int sample_rate) {
	dsp->fSampleRate = sample_rate;
	dsp->fConst0 = min(192000.0f, max(1.0f, (float)dsp->fSampleRate));
	dsp->fConst1 = (3.14159274f / dsp->fConst0);
	dsp->fConst2 = (6.28318548f / dsp->fConst0);
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
	ui_interface->openVerticalBox(ui_interface->uiInterface, "faustpeakeq");
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "freqMid", &dsp->fHslider0, 2200.0f, 400.0f, 3500.0f, 0.100000001f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "gainMid", &dsp->fHslider1, 0.0f, -48.0f, 48.0f, 0.100000001f);
	ui_interface->addHorizontalSlider(ui_interface->uiInterface, "qMid", &dsp->fHslider2, 50.0f, 0.0f, 3000.0f, 0.100000001f);
	ui_interface->closeBox(ui_interface->uiInterface);
}

void computemydsp(mydsp* dsp, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
	FAUSTFLOAT* input0 = inputs[0];
	FAUSTFLOAT* output0 = outputs[0];
	float fSlow0 = (float)dsp->fHslider0;
	float fSlow1 = tanf((dsp->fConst1 * fSlow0));
	float fSlow2 = (2.0f * (1.0f - (1.0f / mydsp_faustpower2_f(fSlow1))));
	float fSlow3 = (1.0f / fSlow1);
	float fSlow4 = (float)dsp->fHslider1;
	int iSlow5 = (fSlow4 > 0.0f);
	float fSlow6 = (float)dsp->fHslider2;
	float fSlow7 = sinf((dsp->fConst2 * fSlow0));
	float fSlow8 = (dsp->fConst1 * ((fSlow6 * powf(10.0f, (0.0500000007f * fabsf(fSlow4)))) / fSlow7));
	float fSlow9 = (dsp->fConst1 * (fSlow6 / fSlow7));
	float fSlow10 = (iSlow5 ? fSlow9 : fSlow8);
	float fSlow11 = (1.0f - (fSlow3 * (fSlow10 - fSlow3)));
	float fSlow12 = ((fSlow3 * (fSlow3 + fSlow10)) + 1.0f);
	float fSlow13 = (iSlow5 ? fSlow8 : fSlow9);
	float fSlow14 = ((fSlow3 * (fSlow3 + fSlow13)) + 1.0f);
	float fSlow15 = (1.0f - (fSlow3 * (fSlow13 - fSlow3)));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (fSlow2 * dsp->fRec0[1]);
			dsp->fRec0[0] = ((float)input0[i] - (((dsp->fRec0[2] * fSlow11) + fTemp0) / fSlow12));
			output0[i] = (FAUSTFLOAT)(((fTemp0 + (dsp->fRec0[0] * fSlow14)) + (dsp->fRec0[2] * fSlow15)) / fSlow12);
			dsp->fRec0[2] = dsp->fRec0[1];
			dsp->fRec0[1] = dsp->fRec0[0];
		}
	}
}

#ifdef __cplusplus
}
#endif

#endif
