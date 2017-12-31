#pragma once
#include "../Elements/state.h"
#include "../Elements/alphabet.h"
#include "../Elements/symbol.h"

#include <set>
#include <cctype> // is digit
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class nfa{
   
   private:
   set<state> vector_state;
   alphabet alphabet_;
   
   public:
   
   //Constructor por defecto
   nfa();
   
   //Destructor por defecto
   ~nfa();
   
   //Devuelvo si se ha creado el nfa o no
   bool empty();
   
   //Destruyo el vector de estados
   void destroy();
   
   //Leo por pantalla el NFA 
   istream& read(istream& is);
   
   //Imprimo los estados de muerte
   void show_death_state();
   
   //Analiza la cadena y llama a analyze_string_rec para formar caminos recursivamente
   void analyze_string(const string&);
   
   //Va formando caminos si hay un estado con mas de una transicion para una cadena de entrada y muestra si para ese camino se acepta
   bool analyze_string_rec(int&,int,const string&,int,string&);
   
   //Devuelve el conjunto al que podemos llegar con epsilon_transition
   set<int> epsilon_transition(const int);
   
   //Imprimo el camino
   void print_way(int&,const string&);
   
   //Imprimo si esta aceptado o no y lo devuelvo
   bool is_way_accepted(const int&);
   
   //Imprimo el nfa
   void print();
   
   //Compruebo si el nfa es dfa(si para cada simbolo del alfabeto tiene una y solo una transición)
   bool is_dfa();
};