#include "m_pd.h"
#include "stdlib.h"

static t_class *multitimbral_class;

typedef struct _multitimbral {
  	t_object  x_obj;
	t_outlet *noteon_list_out;
	t_outlet *noteoff_out;
	t_int nr_of_slots;
} t_multitimbral;

static int* slots = 0; 

void noteon(t_multitimbral *x, t_floatarg note_number){
	
	int i;	
	for(i=0; i<x->nr_of_slots; i++){
		if(slots[i] == (int)note_number){
			t_atom list[2];
			SETFLOAT(&list[0], i);
			SETFLOAT(&list[1], (int)note_number);
			outlet_list(x->noteon_list_out, gensym("list"), 2, &list[0]);
			return;
		}
	}

	for(i=0; i<x->nr_of_slots; i++){
		if(slots[i] == -1){
			slots[i] = (int)note_number;
			t_atom list[2];
			SETFLOAT(&list[0], i);
			SETFLOAT(&list[1], (int)note_number);
			outlet_list(x->noteon_list_out, gensym("list"), 2, &list[0]);
			return;
		}
	}
}

void noteoff(t_multitimbral *x, t_floatarg note_number){
	int i;
	for(i=0; i<x->nr_of_slots; i++){
		if(slots[i] == (int)note_number){
			//TODO Skal vel vere i og ikkje note_number?
			outlet_float(x->noteoff_out, i);
			slots[i] = -1;
			return;
		}
	}
}

void *multitimbral_new(t_floatarg f){
  	t_multitimbral *x = (t_multitimbral *)pd_new(multitimbral_class);

	x->nr_of_slots = (int)f;
	slots = malloc(sizeof(int) * x->nr_of_slots); 	

	int i;
	for(i=0; i<x->nr_of_slots; i++){
		slots[i] = -1;	
	}

	class_addfloat(multitimbral_class, noteon);
	inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("noteoff"));

	x->noteon_list_out = outlet_new(&x->x_obj, gensym("list"));
	x->noteoff_out = outlet_new(&x->x_obj, gensym("float"));

  	return (void *)x;
}

void multitimbral_setup(void){
	multitimbral_class = class_new(
		gensym("multitimbral"),
			(t_newmethod)multitimbral_new,
			0, 
			sizeof(t_multitimbral),
			CLASS_DEFAULT,
			A_DEFFLOAT,
			0
	);
	class_addmethod(multitimbral_class, (t_method)noteoff, gensym("noteoff"), A_DEFFLOAT, 0);
}
