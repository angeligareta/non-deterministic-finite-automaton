#include "state.h"

state::state(){
    identifier=-1;
    initial=0;
    final=0;
}

state::state(const state& state_in){
    identifier= state_in.identifier;
    initial= state_in.initial;
    final=state_in.final; 
    vector_transition = state_in.vector_transition;
}
   
state::~state(){
    destroy();
}

void state::destroy(){
    vector_transition.clear();
}

void state::set_transition(const symbol& symbol_in,int num_in){
    
    // Inicializamos duplciate a 0
    bool duplicate=0;
    
    //Vemos a ver si ya hay una transicion para el simbolo
    for(set<transition>::iterator it=vector_transition.begin(); it!=vector_transition.end();++it){
        transition transition_temp= *it;
        // Si encuentro una transicion con el mismo simbolo, le inserto otro elemento
        if(transition_temp.symbol_entry==symbol_in){
            duplicate=1;
            transition_temp.vector_next_state.insert(num_in);
            // Como no puedo modificar un const iterator lo borro e inserto el nuevo
            vector_transition.erase(*it);
            vector_transition.insert(transition_temp);
        }
    }
           
    if (duplicate==0){
        transition transition_temp(symbol_in,num_in);  
        vector_transition.insert(transition_temp);    
    }
    
}
   
void state::set_identifier(int identifier_in){
    identifier=identifier_in;
}
   
void state::set_initial(bool initial_in){
    initial=initial_in;
}
   
void state::set_final(bool final_in){
    final = final_in;
}

int state::get_number_transition(){
    
    int total_number_transition=0;
    
    for(set<transition>::iterator it=vector_transition.begin(); it!=vector_transition.end();++it)
        total_number_transition+= (*it).vector_next_state.size();
    
    return total_number_transition;
}
   
int state::get_identifier() const{
    return identifier;
}

bool state::is_death_state(){
    
    if(final!=true){
        for(set<transition>::iterator it=vector_transition.begin(); it!=vector_transition.end();++it){
            transition transition_temp = *it;
            set<int> vector_next_state=transition_temp.get_next_state();
            for(set<int>::iterator it2=vector_next_state.begin(); it2!=vector_next_state.end();++it2)
                if(*it2!=identifier)
                    return false;
        }
        return true;
    }
    else 
        return false;
        
}

set<int> state::get_next_state(const symbol& symbol_in) const{
    
    set<int> vector_next_state;
    
    for(set<transition>::iterator it=vector_transition.begin(); it!=vector_transition.end();++it){
        transition transition_temp = *it;
        if(transition_temp.symbol_entry==symbol_in)
            vector_next_state=transition_temp.get_next_state();
    }
    
    return vector_next_state;
}
   
bool state::get_initial() const{
    return initial;
}
   
bool state::get_final() const{
    return final;
}

void state::print_transition(){
    for(set<transition>::iterator it=vector_transition.begin(); it!=vector_transition.end();++it){
        transition transition_temp = *it;
        transition_temp.print();
    }
}

state& state::operator=(const state &state_in){
    this->identifier= state_in.identifier;
    this->initial= state_in.initial;
    this->final=state_in.final;
    this->vector_transition = state_in.vector_transition;
        
    return *this;
}

int state::operator==(const state &state_in) const{
    if(this->identifier != state_in.identifier) return 0;
    if(this->initial != state_in.initial) return 0;
    if(this->final != state_in.final) return 0;
    if(this->vector_transition.size() != state_in.vector_transition.size()) return 0;
    
    set<transition>::iterator iter1=vector_transition.begin();
    set<transition>::iterator iter2=state_in.vector_transition.begin();
    while(iter1!=vector_transition.end()){
        if(!(*iter1 ==*iter2))
            return 0;
        iter1++; iter2++;
    }
    return 1;
}

int state::operator<(const state &state_in) const{
    return (identifier < state_in.identifier);
}