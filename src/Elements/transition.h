#pragma once
#include <set>
#include "symbol.h"

using namespace std;


class transition{
   
   public:
   
   set<int> vector_next_state; //Numero del siguiente estado
   symbol symbol_entry; // Simbolo del estado
   
   transition();
   
   transition(const symbol&,int);
   
   transition(const transition&);
   
   ~transition();
   
   void print();
   
   set<int> get_next_state();
   
   transition& operator=(const transition&);

   int operator==(const transition&) const;

   int operator<(const transition&) const;
};