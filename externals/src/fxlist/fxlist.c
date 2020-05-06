#include "m_pd.h"

static t_class *fxlist_class;

typedef struct _fxlist {
    t_object  x_obj;
    t_int num_fx;
    t_int* fx_list;
    t_int* enabled_list;
    t_outlet** outlets_fx;
    t_outlet* outlet_fxinputindex; //which index to connect fxinput throw to
    t_outlet* outlet_fx_list;
    t_outlet* outlet_fxoutputindex; //which index's throw to connect to fxoutput
} t_fxlist;

void output_fx_list(t_fxlist *this_object);
void moveup(t_fxlist *this_object, t_floatarg argument);
void movedown(t_fxlist *this_object, t_floatarg argument);
int index_of(t_int list[], t_int number, t_int array_size);
void output_routing(t_fxlist *this_object);
void setorder(t_fxlist *this_object, t_symbol *s, int argc, t_atom *argv);

void fxlist_bang(t_fxlist *this_object){
    output_fx_list(this_object);
    output_routing(this_object);
}

void output_fx_list(t_fxlist *this_object){
	t_atom out[this_object->num_fx];
	for(int i=0; i<this_object->num_fx; i++){
		SETFLOAT(out+i, (t_float)this_object->fx_list[i]);
	}
	outlet_list(this_object->outlet_fx_list, gensym("list"), this_object->num_fx, out); 
}

void moveup(t_fxlist *this_object, t_floatarg argument){
	t_int fx_to_move_up = (t_int)argument;
	t_int fx_index = index_of(this_object->fx_list, fx_to_move_up, this_object->num_fx);
	if(fx_index > 0){
		t_int num_in_place = this_object->fx_list[fx_index-1];
		this_object->fx_list[fx_index-1] = fx_to_move_up;
		this_object->fx_list[fx_index] = num_in_place;
	}
	output_fx_list(this_object);
    output_routing(this_object);
}

void movedown(t_fxlist *this_object, t_floatarg argument){
	t_int fx_to_move_down = (t_int)argument;
	t_int fx_index = index_of(this_object->fx_list, fx_to_move_down, this_object->num_fx);
	if(fx_index >= 0 && fx_index < this_object->num_fx-1){
		t_int num_in_place = this_object->fx_list[fx_index+1];
		this_object->fx_list[fx_index+1] = fx_to_move_down;
		this_object->fx_list[fx_index] = num_in_place;
	}
	output_fx_list(this_object);
    output_routing(this_object);
}

int index_of(t_int list[], t_int number, t_int array_size){
	for(int i=0; i<array_size; i++){
		if(list[i] == number){
			return i;
		}
	}
	return -1;
}

void enable(t_fxlist *this_object, t_floatarg arg_fxindex, t_floatarg arg_enable){
    t_int fxindex = (t_int)arg_fxindex;
    t_int enable = (t_int)arg_enable;
    this_object->enabled_list[fxindex] = enable;
    output_routing(this_object);
}

void output_routing(t_fxlist *this_object){

    t_int input_index = -1;
    for(int i=0; i<this_object->num_fx; i++){
        if(this_object->enabled_list[this_object->fx_list[i]] == 1){
            input_index = this_object->fx_list[i];
            break;
        }
    }

    outlet_float(this_object->outlet_fxinputindex, input_index);

    for(int i=0; i<this_object->num_fx; i++){
        if(this_object->enabled_list[this_object->fx_list[i]] == 1){
            t_int from_id = this_object->fx_list[i];
            t_int to_id = -1;

            for(int j=i+1; j<this_object->num_fx; j++){
                if(this_object->enabled_list[this_object->fx_list[j]] == 1){
                    to_id = this_object->fx_list[j];
                    break;
                }
            }

            if(from_id > -1 && to_id > -1){
                outlet_float(this_object->outlets_fx[from_id], to_id);
            }
            
        }
    }

    t_int output_index = -1;

    for(int i=this_object->num_fx-1; i>=0; i--){
        if(this_object->enabled_list[this_object->fx_list[i]] == 1){
            output_index = this_object->fx_list[i];
            break;
        }
    }

    outlet_float(this_object->outlet_fxoutputindex, output_index);

}

void setorder(t_fxlist *this_object, t_symbol *s, int argc, t_atom *argv){
	if(argc != this_object->num_fx){
		post("Error: Wrong number of arguments");
		return;
	}
	for(int i=0; i<argc; i++){
		t_int current_value = (t_int)atom_getfloat(&argv[i]);
		if(current_value >= this_object->num_fx){
			post("Error: FX index too high");
			return;
		}
		for(int j=0; j<argc; j++){
			if(j != i){
				t_int value_to_compare = (t_int)atom_getfloat(&argv[j]);
				if(current_value == value_to_compare){
					post("Error: Duplicate values");
					return;
				}
			}
		}
	}

	for(int i=0; i<argc; i++){
		this_object->fx_list[i] = (t_int)atom_getfloat(&argv[i]);	
	}

	output_fx_list(this_object);
    output_routing(this_object);
}

void *fxlist_new(t_floatarg num_fx_arg) {
    t_fxlist *this_object = (t_fxlist *)pd_new(fxlist_class);
    this_object->num_fx = (int)num_fx_arg;
    this_object->fx_list = malloc(sizeof(t_int) * this_object->num_fx);
    this_object->enabled_list = malloc(sizeof(t_int) * this_object->num_fx);
    this_object->outlets_fx = malloc(sizeof(t_outlet*) * this_object->num_fx);
    for(int i=0; i<this_object->num_fx; i++){
		this_object->fx_list[i] = i;
	}
    this_object->outlet_fxoutputindex = outlet_new(&this_object->x_obj, &s_list);
    for(int i=0; i<this_object->num_fx; i++){		
		this_object->outlets_fx[i] = outlet_new(&this_object->x_obj, &s_float);
	}
    this_object->outlet_fxinputindex = outlet_new(&this_object->x_obj, &s_list);
    this_object->outlet_fx_list = outlet_new(&this_object->x_obj, &s_list);
    return (void *)this_object;
}

void fxlist_free(t_fxlist *this_object){
    outlet_free(this_object->outlet_fxinputindex);
    outlet_free(this_object->outlet_fx_list);
    outlet_free(this_object->outlet_fxoutputindex);
    for(int i=0; i<this_object->num_fx; i++){
		outlet_free(this_object->outlets_fx[i]);
	}
	free(this_object->fx_list);
	free(this_object->enabled_list);
	free(this_object->outlets_fx);
}

void fxlist_setup(void) {
    fxlist_class = class_new(
        gensym("fxlist"),
        (t_newmethod)fxlist_new,
        (t_method)fxlist_free,
        sizeof(t_fxlist),
        CLASS_DEFAULT,
        A_DEFFLOAT,
        0
    );

    class_addbang(fxlist_class, fxlist_bang);

    class_addlist(fxlist_class, setorder);

    class_addmethod(
        fxlist_class,  
        (t_method)moveup, 
        gensym("moveup"),  
        A_DEFFLOAT,
        0
    );

	class_addmethod(
		fxlist_class,  
		(t_method)movedown, 
		gensym("movedown"),  
		A_DEFFLOAT,
		0
	);

    class_addmethod(
		fxlist_class,  
		(t_method)enable, 
		gensym("enable"),  
		A_DEFFLOAT,
		A_DEFFLOAT,
		0
	);
    
}