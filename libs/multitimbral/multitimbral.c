#include "m_pd.h"
#include "stdlib.h"

static t_class *multitimbral_class;

typedef struct _multitimbral {
  	t_object  x_obj;
	t_outlet *noteon_list_out;
	t_outlet *noteoff_out;
	t_int nr_of_slots;
} t_multitimbral;

typedef struct _slotstr {
	int notenumber;
	int state;
} slotstr;

slotstr *slotstr_array;

int find_available_slot(int);

static int* cqueue = 0;
void queue_insert(int);
void queue_delete_element(int);
int queue_dequeue();
void queue_display();
int queue_front = -1;
int queue_rear = -1;
int queue_max;

const int SLOT_AVAILABLE = 1;
const int SLOT_QUEUED = 2;
const int SLOT_UNAVAILABLE = 3;

void noteon(t_multitimbral *x, t_floatarg note_number){

	int i;	
	for(i=0; i<x->nr_of_slots; i++){
		if(slotstr_array[i].notenumber == (int)note_number && slotstr_array[i].state != SLOT_AVAILABLE){
			queue_delete_element(i);
			slotstr_array[i].state = SLOT_UNAVAILABLE;
			t_atom list[2];
			SETFLOAT(&list[0], i);
			SETFLOAT(&list[1], (int)note_number);
			outlet_list(x->noteon_list_out, gensym("list"), 2, &list[0]);
			return;
		}

	}

	int available_slot = find_available_slot(x->nr_of_slots);

	if(available_slot == -1){
		if(queue_isempty() == 1){
			return;
		}
		else {
			int dequeued = queue_dequeue();
			slotstr_array[dequeued].notenumber = (int)note_number;
			slotstr_array[dequeued].state = SLOT_UNAVAILABLE;
			t_atom list[2];
			SETFLOAT(&list[0], dequeued);
			SETFLOAT(&list[1], (int)note_number);
			outlet_list(x->noteon_list_out, gensym("list"), 2, &list[0]);
			return;
		}
	}
	else {
		slotstr_array[available_slot].notenumber = (int)note_number;
		slotstr_array[available_slot].state = SLOT_UNAVAILABLE;
		t_atom list[2];
		SETFLOAT(&list[0], available_slot);
		SETFLOAT(&list[1], (int)note_number);
		outlet_list(x->noteon_list_out, gensym("list"), 2, &list[0]);
		return;
	}
}

int find_available_slot(int num_slots){
	int available_slot = -1;
	int i;
	for(i=0; i<num_slots; i++){
		if(slotstr_array[i].state == SLOT_AVAILABLE){
			available_slot = i;
			break;
		}
	}
	return available_slot;
}

void noteoff(t_multitimbral *x, t_floatarg note_number){
	int i;
	for(i=0; i<x->nr_of_slots; i++){
		if(slotstr_array[i].notenumber == (int)note_number){
			outlet_float(x->noteoff_out, i);
			queue_insert(i);
			slotstr_array[i].state = SLOT_QUEUED;
			return;
		}
	}
}

void setavailable(t_multitimbral *x, t_floatarg note_number){
	int dequeued = queue_dequeue();
	slotstr_array[dequeued].state = SLOT_AVAILABLE;
}

void *multitimbral_new(t_floatarg f){
  	t_multitimbral *x = (t_multitimbral *)pd_new(multitimbral_class);

	x->nr_of_slots = (int)f;	
	cqueue = malloc(sizeof(int) * x->nr_of_slots); 

	slotstr_array = malloc(sizeof(slotstr) * x->nr_of_slots); 

	queue_max = x->nr_of_slots;

	int i;
	for(i=0; i<x->nr_of_slots; i++){
		slotstr_array[i].state = SLOT_AVAILABLE;	
	}

	class_addfloat(multitimbral_class, noteon);
	inlet_new(&x->x_obj, &x->x_obj.ob_pd, gensym("float"), gensym("setavailable"));
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
	class_addmethod(multitimbral_class, (t_method)setavailable, gensym("setavailable"), A_DEFFLOAT, 0);
}

void queue_insert(int element){
	if((queue_front == 0 && queue_rear == queue_max-1) || (queue_front == queue_rear+1)){
		return;
	}
	if(queue_front == -1){
		queue_front = 0;
	}
	if(queue_rear == queue_max-1){
		queue_rear = 0;
	}
	else {
		queue_rear = queue_rear+1;
	}

	cqueue[queue_rear] = element;
}

int queue_dequeue(){
	int element;
	if(queue_isempty() == 1){
		return;
	}
	element = cqueue[queue_front];
	if(queue_front == queue_rear){
		queue_front = -1;
		queue_rear = -1;
	}
	else if(queue_front == queue_max-1) {
		queue_front = 0;
	}
	else {
		queue_front = queue_front+1;
	}
	return element;
}

int queue_isempty(){
	if(queue_front == -1){
		return 1;
	}
	else {
		return 0;
	}
}

void queue_delete_element(int element){
	int tmp_rear = -1;
	int tmp_cqueue[queue_max];

	while(queue_isempty() == 0){
		int dequeued_element = queue_dequeue();
		if(dequeued_element != element){
			tmp_rear = tmp_rear+1;
			tmp_cqueue[tmp_rear] = dequeued_element;
		}
	}

	//TODO Use memcpy
	int i;
	for(i=0; i<queue_max; i++){
		cqueue[i] = tmp_cqueue[i];
	}

	if(tmp_rear == -1){
		queue_front = -1;
	}
	else {
		queue_front = 0;
	}
	queue_rear = tmp_rear;
}

void queue_display(){
	if(queue_front == -1){
		post("Queue is empty\n");
		return;
	}

	int i = queue_front;

	if(queue_front <= queue_rear){
		while(i <= queue_rear){
			post("%d ", cqueue[i++]);

		}
	}

	else {
		while(i<=queue_max-1){
			post("%d ", cqueue[i++]);

		}
		
		i=0;
		
		while(i<=queue_rear){
			post("%d ", cqueue[i++]);
		}

	}

}
