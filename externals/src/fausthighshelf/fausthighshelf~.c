#include <stdlib.h>
#include "m_pd.h"
#include "math.h"

static t_class *fausthighshelf_tilde_class;

typedef struct _fausthighshelf_tilde
{
	t_object object_properties;
	t_float f;
	t_sample* in_buffer;

	t_int fSamplingFreq;
	t_float fConst0;
	t_float fVec0[2];
	t_float fRec1[2];
	t_float fRec0[3];
	t_float fRec3[2];
	t_float fRec2[3];

	t_outlet *x_out1;

	t_inlet *in_freq;

	t_inlet *in_gain;

	t_float gain;

	t_float freq;

} t_fausthighshelf_tilde;

void fausthighshelf_instance_clear(t_fausthighshelf_tilde *this_object)
{
	/* C99 loop */
	{
		int l0;
		for (l0 = 0; (l0 < 2); l0 = (l0 + 1))
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
		for (l2 = 0; (l2 < 3); l2 = (l2 + 1))
		{
			this_object->fRec0[l2] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l3;
		for (l3 = 0; (l3 < 2); l3 = (l3 + 1))
		{
			this_object->fRec3[l3] = 0.0f;
		}
	}
	/* C99 loop */
	{
		int l4;
		for (l4 = 0; (l4 < 3); l4 = (l4 + 1))
		{
			this_object->fRec2[l4] = 0.0f;
		}
	}
}

void *fausthighshelf_new(t_floatarg f)
{
	t_fausthighshelf_tilde *this_object = (t_fausthighshelf_tilde *)pd_new(fausthighshelf_tilde_class);

	this_object->x_out1 = outlet_new(&this_object->object_properties, &s_signal);
	this_object->in_freq = floatinlet_new(&this_object->object_properties, &this_object->freq);
	this_object->in_gain = floatinlet_new(&this_object->object_properties, &this_object->gain);

	this_object->freq = 50;

	fausthighshelf_instance_clear(this_object);

	this_object->fSamplingFreq = (t_int)sys_getsr();
	this_object->fConst0 = (3.14159274f / fmin(192000.0f, fmax(1.0f, (float)this_object->fSamplingFreq)));

	return (void *)this_object;
}

t_int *fausthighshelf_tilde_perform(t_int *w)
{
	t_fausthighshelf_tilde *this_object = (t_fausthighshelf_tilde *)(w[1]);
	t_sample *in = (t_sample *)(w[2]);
	t_sample *out = (t_sample *)(w[3]);
	int n = (int)(w[4]);

	for (int i = 0; (i < n); i = (i + 1)) {
        this_object->in_buffer[i] = in[i];
    }

	t_float frequency = fmax(10.0f, this_object->freq);

	float fSlow0 = tanf(this_object->fConst0 * frequency);
	float fSlow1 = (1.0f / fSlow0);
	float fSlow2 = (1.0f / (((fSlow1 + 1.0f) / fSlow0) + 1.0f));
	float fSlow3 = (fSlow1 + 1.0f);
	float fSlow4 = (0.0f - ((1.0f - fSlow1) / fSlow3));
	float fSlow5 = (1.0f / fSlow3);
	float fSlow6 = (((fSlow1 + -1.0f) / fSlow0) + 1.0f);
	float fSlow7 = (1.0f / (fSlow0 * fSlow0));
	float fSlow8 = (2.0f * (1.0f - fSlow7));
	float fSlow9 = powf(10.0f, (0.0500000007f * (float)this_object->gain));
	float fSlow10 = (0.0f - fSlow1);
	float fSlow11 = (2.0f * (0.0f - fSlow7));
	/* C99 loop */
	{
		int i;
		for (i = 0; (i < n); i = (i + 1)) {
			float fTemp0 = (float)this_object->in_buffer[i];
			this_object->fVec0[0] = fTemp0;
			this_object->fRec1[0] = ((fSlow4 * this_object->fRec1[1]) + (fSlow5 * (this_object->fVec0[1] + fTemp0)));
			this_object->fRec0[0] = (this_object->fRec1[0] - (fSlow2 * ((fSlow6 * this_object->fRec0[2]) + (fSlow8 * this_object->fRec0[1]))));
			this_object->fRec3[0] = ((fSlow4 * this_object->fRec3[1]) + (fSlow5 * ((fSlow1 * fTemp0) + (fSlow10 * this_object->fVec0[1]))));
			this_object->fRec2[0] = (this_object->fRec3[0] - (fSlow2 * ((fSlow6 * this_object->fRec2[2]) + (fSlow8 * this_object->fRec2[1]))));
			out[i] = (t_sample)(fSlow2 * ((this_object->fRec0[2] + (this_object->fRec0[0] + (2.0f * this_object->fRec0[1]))) + (fSlow9 * (((fSlow7 * this_object->fRec2[0]) + (fSlow11 * this_object->fRec2[1])) + (fSlow7 * this_object->fRec2[2])))));
			this_object->fVec0[1] = this_object->fVec0[0];
			this_object->fRec1[1] = this_object->fRec1[0];
			this_object->fRec0[2] = this_object->fRec0[1];
			this_object->fRec0[1] = this_object->fRec0[0];
			this_object->fRec3[1] = this_object->fRec3[0];
			this_object->fRec2[2] = this_object->fRec2[1];
			this_object->fRec2[1] = this_object->fRec2[0];
			
		}
		
	}

	return (w + 5);
}

void fausthighshelf_tilde_dsp(t_fausthighshelf_tilde *this_object, t_signal **sp)
{
	dsp_add(fausthighshelf_tilde_perform, 4, this_object, sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
	this_object->in_buffer = malloc(sp[0]->s_n * sizeof(t_sample));
}

void fausthighshelf_tilde_free(t_fausthighshelf_tilde *this_object)
{
	free(this_object->in_buffer);
	/*free(this_object->fVec0);
	free(this_object->fRec1);
	free(this_object->fRec0);
	free(this_object->fRec3);
	free(this_object->fRec2);*/
}

void fausthighshelf_tilde_setup(void)
{
	fausthighshelf_tilde_class = class_new(
		gensym("fausthighshelf~"),
		(t_newmethod)fausthighshelf_new,
		(t_method)fausthighshelf_tilde_free,
		sizeof(t_fausthighshelf_tilde),
		CLASS_DEFAULT,
		A_DEFFLOAT,
		0);

	class_addmethod(fausthighshelf_tilde_class, (t_method)fausthighshelf_instance_clear, gensym("clear"), 0);

	CLASS_MAINSIGNALIN(fausthighshelf_tilde_class, t_fausthighshelf_tilde, f);
	class_addmethod(fausthighshelf_tilde_class, (t_method)fausthighshelf_tilde_dsp, gensym("dsp"), A_CANT);
}
