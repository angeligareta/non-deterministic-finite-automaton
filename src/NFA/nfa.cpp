#include "nfa.h"

//Constructor por defecto
nfa::nfa(){}

//Destructor por defecto
nfa::~nfa(){
    destroy();
}

//Destruyo el vector de estados
void nfa::destroy(){
    vector_state.clear();
}

//Devuelvo si se ha creado el nfa o no
bool nfa::empty(){
    return vector_state.empty();
}

//Imprimo los estados de muerte
void nfa::show_death_state(){
    
    int counter=0;
    
    cout << "\nLos estados de muerte son: " << endl;
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it){
        state state_temp=*it;
        if(state_temp.is_death_state()==true){
            cout << "Estado numero " << state_temp.get_identifier() << endl;
            counter++;
        }
    }
    
    if(counter==0)
        cout << "\nNo hay estados de muerte..." << endl;    
}

//Analiza la cadena y llama a analyze_string_rec para formar caminos recursivamente
void nfa::analyze_string(const string& string_in){
    
    cout << "\nCadena de entrada: " << string_in << endl << endl;
    
    bool error=false;
    
    // Si ha introducido una cadena con un simbolo que no pertenezca al alfabeto salgo
    for(int i=0;i<string_in.length();i++){
        symbol symbol_entry(string_in[i]); 
        if(!alphabet_.it_belongs(symbol_entry))
            error=true;
    }
    
    if(error==false){
        
        int initial_state;
        
        //Me coloco en el primer estado
        for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it){
            state state_temp=*it;
            if(state_temp.get_initial()==true)
                initial_state=state_temp.get_identifier();
        }
        
        int way_counter=0;
        
        string string_out="";
        //Empiezo a pasar de estado a estado dependiendo de la entrada
        bool accepted= analyze_string_rec(way_counter,initial_state,string_in,0,string_out);
        
        cout << endl << "Decisión final:" << endl;
        
        if(accepted==true)
            cout << endl << "\t\t¡LA CADENA ESTA ACEPTADA!" << endl;
        else
            cout << endl << "\t\tLA CADENA NO ESTA ACEPTADA" << endl;
        
    }
    
    else
        cout << "ERROR - La cadena tiene simbolos que no pertenecen al alfabeto" << endl;    
}

//Va formando caminos si hay un estado con mas de una transicion para una cadena de entrada y muestra si para ese camino se acepta
bool nfa::analyze_string_rec(int& way_counter,int number_actual_state, const string& string_in,int counter,string& string_out){
    
    //Usamos este bool para la decisión final
    bool total_accepted=0;
    
    // Voy leyendo la cadena y haciendo caminos
    while(counter < string_in.length() && (number_actual_state!=-1)){
        
        //Hacemos epsilon_transition, si podemos llegar a algun sitio nuevo creamos otro camino
        set<int> set_epsilon_transition = epsilon_transition(number_actual_state);
        
        string string_temp=string_out;
        //Por cada epsilon_transition que nos lleve a otro estado hacemos un camino
        for(set<int>::iterator iter=set_epsilon_transition.begin();iter!=set_epsilon_transition.end();++iter){
            string_temp+=static_cast<ostringstream*>( &(ostringstream() << number_actual_state) )->str();
            string_temp+="~";
            string_temp+=static_cast<ostringstream*>( &(ostringstream() << *iter) )->str();
            total_accepted+=analyze_string_rec(way_counter,*iter,string_in,counter,string_temp); 
            string_temp="";
        }
            
        //Vamos guardando los caminos en un string
        
        //Aqui añadimos el estado actual
        string_out+= static_cast<ostringstream*>( &(ostringstream() << number_actual_state) )->str();
        
        //Cogemos el simbolo actual
        symbol symbol_entry(string_in[counter]);
        string_out+=symbol_entry.symbol_;
        
        //Buscamos el estado en el que estamos
        for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it){
            state state_temp=*it;
            if(state_temp.get_identifier()==number_actual_state){
                
                //Cogemos el proximo o proximos estados para el simbolo introducido
                set<int> vector_next_state = state_temp.get_next_state(symbol_entry);
                
                // Si no hay transiciones es que va a NULL
                if(!vector_next_state.empty()){
                    //Si es mayor que 1 creamos otro camino
                    int next_counter=1;
                    for(set<int>::iterator iter=vector_next_state.begin();iter!=vector_next_state.end();++iter){
                        if(next_counter==1)
                            number_actual_state=*iter;
                        else{
                            string string_temp=string_out+ static_cast<ostringstream*>( &(ostringstream() << *iter) )->str();
                            total_accepted+=analyze_string_rec(way_counter,*iter,string_in,counter+1,string_temp);  
                        }
                        next_counter++; 
                    }
                    string_out+= static_cast<ostringstream*>( &(ostringstream() << number_actual_state) )->str();
                }
                else{
                    number_actual_state=-1;
                    string_out+= "-";
                }
                break;
            }
        }
        
        counter++;
    }
    
    // Volvemos a hacer epsilon_transition cuando hayamos terminado
    
    //Hacemos epsilon_transition, si podemos llegar a algun sitio nuevo creamos otro camino
    set<int> set_epsilon_transition = epsilon_transition(number_actual_state);
        
    string string_temp=string_out;
    //Por cada epsilon_transition que nos lleve a otro estado hacemos un camino
    for(set<int>::iterator iter=set_epsilon_transition.begin();iter!=set_epsilon_transition.end();++iter){
        string_temp+=static_cast<ostringstream*>( &(ostringstream() << number_actual_state) )->str();
        string_temp+="~";
        string_temp+=static_cast<ostringstream*>( &(ostringstream() << *iter) )->str();
        total_accepted+=analyze_string_rec(way_counter,*iter,string_in,counter,string_temp); 
        string_temp="";
    }
    
    print_way(way_counter,string_out);
    
    total_accepted+=is_way_accepted(number_actual_state);
    
    return total_accepted;
}

//Devuelve el conjunto al que podemos llegar con epsilon_transition
set<int> nfa::epsilon_transition(const int number_actual_state){
    
    // Nos colocamos en el estado en que estamos
    state actual_state;
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it)
        if((*it).get_identifier()==number_actual_state)
            actual_state=*it; 
    
    // Vemos a que estados podemos ir desde el que estamos con epsilon
    symbol symbol_epsilon('~');
    set<int> vector_next_state=actual_state.get_next_state(symbol_epsilon);
    
    // Obviamos el estado en el que estamos
    vector_next_state.erase(number_actual_state);
    
    return vector_next_state;
}

//Imprimo el camino
void nfa::print_way(int& way_counter,const string& string_out){
    
    cout << endl << "\n\t\t\tCAMINO " << ++way_counter << endl << endl;
    
    cout << "Estado actual\t\t" << "Entrada\t\t" << "Siguiente estado" << endl;
    
    for(int i=0;i<string_out.size();i++){
        cout << string_out[i];
        if((i+1)%3!=0)
            cout << "\t\t\t";
        else
            cout << endl;
    }  
}

//Imprimo si esta aceptado o no y lo devuelvo
bool nfa::is_way_accepted(const int& number_actual_state){
    
    bool accepted=0;
    
    // Miro si para el estado que estoy la cadena esta aceptada
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it){
        state state_temp=*it;
        if(state_temp.get_identifier()==number_actual_state) //Veo en que estado me he quedado
            if(state_temp.get_final()) //Si me he quedado en un estado de aceptación devuelvo true
                accepted=true;
    }
    
    if(accepted==true)
        cout << endl << "\t\t¡LA CADENA ESTA ACEPTADA!" << endl;
    else
        cout << endl << "\t\tLA CADENA NO ESTA ACEPTADA" << endl;
    
    return accepted;
        
}

//Leo por pantalla el NFA y si no tiene errores lo abro
istream& nfa::read(istream& is){
    
    destroy();
    
    bool error=0;
    
    int state_number;
    int state_count=0;
    
    is >> state_number;
    
    int initial_state;
    
    is >> initial_state;
    
    int id; bool final; int num_transition;
    
    while(state_count < state_number && error==0){
        
        state state_temp;
        
        is >> id;
        
        state_temp.set_identifier(id);
        
        if(id==initial_state)
            state_temp.set_initial(true);
        
        is >> final;
        
        if(final==true)
            state_temp.set_final(true);
        
        is >> num_transition;
        
        string symbol_string;
        int next_state;
        
        for(int i=0;i<num_transition;i++){
            is >> symbol_string;
            if(isdigit(symbol_string[0]))
                error=1;
            is >> next_state;
            symbol symbol_(symbol_string);
            alphabet_.insert(symbol_);
            state_temp.set_transition(symbol_,next_state);
        }
        
        if(num_transition!=state_temp.get_number_transition())
            error=1;
        
        vector_state.insert(state_temp);
        
        state_count++;
    }
    
    //El numero de estados no es igual al original error
    if(state_number!=vector_state.size() || error==1){
        cout << "\nERROR- El fichero introducido tiene formato incorrecto" << endl;
        destroy();
    }
    else
	    cout << "\nFICHERO ABIERTO" << endl;
   
}

//Imprimo el nfa
void nfa::print(){
    
    alphabet_.print();
    
    cout << endl << "Este es el nfa introducido: \n" << endl;
    
    cout << vector_state.size() << endl;
    
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it){
        state state_temp=*it;
        if(state_temp.get_initial()==true)
            cout << state_temp.get_identifier() << endl;
    }
    
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it){
        state state_temp=*it;
        cout << state_temp.get_identifier() << " ";
        cout << state_temp.get_final() << " ";
        cout << state_temp.get_number_transition();
        //Mostramos sus transiciones
        state_temp.print_transition();
        cout << endl;
    }
    
}

//Compruebo si el nfa es dfa(si para cada simbolo del alfabeto tiene una y solo una transición)
bool nfa::is_dfa(){
    
    //Para cada estado
    for(set<state>::iterator it=vector_state.begin(); it!=vector_state.end();++it){
        state state_temp = *it;
        //Para cada letra del alfabeto
        for(set<symbol>::iterator it2=alphabet_.alphabet_.begin();it2!=alphabet_.alphabet_.end();++it2){
            symbol symbol_temp = *it2;
            // Compruebo que para cada cadena de entrada solo tenga una transición
            set<int> vector_next_state=state_temp.get_next_state(symbol_temp);
            if(vector_next_state.size()!=1)
                return false;
        }
    }
    
    return true;
}