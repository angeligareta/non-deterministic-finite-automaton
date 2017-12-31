#include "NFA/nfa.h"

#include <cstdio>
#include <cstdlib> //Para system clear
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

int main(){
    
    ifstream nfa_file;
    nfa nfa_;
    
    int opcion;
    
    // Menú
    do{
        cout << "\n\n" << "╔" << string(40, '-') << " Selecciona una opción " << string(40, '-') << "╗" <<  "\n" << endl;
        
        cout << "\t⬤ Opción 0: Salir" << endl;
        cout << "\t⬤ Opción 1: Leer NFA (OBLIGATORIO)" << endl;
        cout << "\t⬤ Opción 2: Mostrar NFA"<< endl;
        cout << "\t⬤ Opción 3: Identificar estados de muerte" << endl;
        cout << "\t⬤ Opción 4: ES DFA" << endl;
        cout << "\t⬤ Opción 5: Analizar cadena" << endl;
        
        cout << "\n" << "╚" << string(103, '-') << "╝" << endl;
        cin >> opcion;
        system("clear");
        
        switch(opcion){
                case 1:
                {
                
                cout << "Introduce el nombre del fichero .nfa" << endl;
                
                string fich_string;
                cin >> fich_string;
                
                //Compruebo si el archivo que ha introducido ya acaba en .nfa, si no se lo pongo
                string string_aux="";
                for(int i=(fich_string.length()-4);i<fich_string.length();i++)
                    string_aux+=fich_string[i];
                
                if(string_aux!=".nfa")
                    fich_string+=".nfa";
                
                cout << "\nBuscando el fichero " << fich_string << "... " << endl;
                
                char *fich = new char [fich_string.length()+1];
                strcpy (fich, fich_string.c_str());
                
	            nfa_file.open(fich);
	            nfa_.read(nfa_file);
	            
	            if(!nfa_file.is_open())
	                cout << "\nERROR - Debe introducir un fichero.nfa correcto primero" << endl;
	            // Cerramos el fichero
	            nfa_file.close();
                break;
                }
                case 2: 
                {
                    if(nfa_.empty()==false) 
                        nfa_.print(); 
                    else
                        cout << "ERROR - Debe introducir un fichero.nfa correcto primero" << endl;
                    break;
                }
                case 3:
                {
                    if(nfa_.empty()==false) 
                        nfa_.show_death_state(); 
                    else
                        cout << "ERROR - Debe introducir un fichero.nfa correcto primero" << endl;
                    break;
                }
                case 4:
                {
                    if(nfa_.empty()==false) {
                        if (nfa_.is_dfa())
                            cout << "El NFA introducido es DFA" << endl;
                        else
                            cout << "El NFA introducido no es DFA" << endl;
                    }
                        
                    else
                        cout << "ERROR - Debe introducir un fichero.nfa correcto primero" << endl;
                    break;
                }
                case 5:
                {  
                    if(nfa_.empty()==false){
                        string string_in;
                        cin >> string_in;
                        nfa_.analyze_string(string_in); 
                    }
                    else
                        cout << "ERROR - Debe introducir un fichero.nfa correcto primero" << endl;
                    break;    
                }
                default: opcion=0;
                
        }
        
    }while (opcion!=0); 
	
}