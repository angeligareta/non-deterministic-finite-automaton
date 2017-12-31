#pragma once
#include "transition.h"

#include <set>
#include <cstdio>
#include <iostream>

using namespace std;

class state{
   
   private:
   
   int identifier;
   bool initial;
   bool final;
   
   public:
   
   set<transition> vector_transition;
   
   state();
   
   state(const state&);
   
   ~state();
   
   void destroy();
   
   void set_identifier(int);
   
   void set_initial(bool);
   
   void set_final(bool);
   
   int get_number_transition();
   
   int get_identifier() const;
   
   bool get_initial() const;
   
   bool get_final() const;
   
   bool is_death_state();
   
   set<int> get_next_state(const symbol&) const;
   
   void set_transition(const symbol&,int);
   
   void print_transition();
   
   state& operator=(const state &state_in);

   int operator==(const state &state_in) const;

   int operator<(const state &state_in) const;
   
};