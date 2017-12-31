#include "transition.h"

transition::transition(){
    vector_next_state.clear();
}

transition::transition(const symbol &symbol_in,int num_in){
    vector_next_state.insert(num_in);
    symbol_entry=symbol_in;
}

transition::transition(const transition &transition_in){
    vector_next_state=transition_in.vector_next_state;
    symbol_entry=transition_in.symbol_entry; 
}
   
transition::~transition(){
    vector_next_state.clear();
}

set<int> transition::get_next_state(){
    return vector_next_state;    
}

transition& transition::operator=(const transition &transition_in){
    this->symbol_entry= transition_in.symbol_entry;
    this->vector_next_state= transition_in.vector_next_state;
    return *this;
}

int transition::operator==(const transition &transition_in) const{
    if( this->vector_next_state  != transition_in.vector_next_state) return 0;
    if( !(this->symbol_entry       == transition_in.symbol_entry)) return 0;
    return 1;
}

int transition::operator<(const transition &transition_in) const{
    return (symbol_entry < transition_in.symbol_entry);
}

void transition::print(){
    
    for(set<int>::iterator iter=vector_next_state.begin();iter!=vector_next_state.end();++iter)
        cout << " " << symbol_entry << " " << *iter;
}