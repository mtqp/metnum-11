#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "printFuncs.h"
#include "intFuncs.h"
#include "Real.h"

using namespace std;

#define it_default 10

void printDouble(double decker){
    char * desmond = (char *) & decker;
    int i;
	cout << "double representation --> " << decker << endl;;
	printNotacion();
	
	unsigned char* bits = (unsigned char*) malloc(sizeof(unsigned char)*8);

    for (i=sizeof(double)-1; i>=0; i--) {
         //printf ("%02X ", desmond[i]);
         printCharsetInBits(desmond[i], bits);
         printf ("%s ", bits);
    }
    printf ("\n");
    
    free(bits);
}

void printCharsetInBits(char set, unsigned char* bits){
	unsigned char pot  = 128;
	unsigned char data = (unsigned char) set;
	
    for(int i=0; i<8; ++i)
    {
        if((data/pot)%2){
        	bits[i] = '1';
        }
        else {
        	bits[i] = '0';
        }
        
        pot /= 2;
    }
}

void printNotacion(){
	cout << "Notacion:" << endl;
	cout << "	izq = + significativa" << endl;
	cout << "	der = - significativa" << endl;
}

int main(int argc, char** argv){
	char t_digitos;	//se usa para el constructor del tipo de datos nuestro
	int cantIteraciones;
	int i = 0;
		
	if(argc<2)
		cout << "use: ./errores [tdigitos] [cantidadIteraciones]" << endl << "El segundo parametro es opcional." << endl;
	else {
		if(argc==2){
			cantIteraciones = it_default;
		}
		else
		{ 
			cantIteraciones = atoi(argv[2]);
		}
		
		//t_digitos = atoi(argv[1]);
		t_digitos = *argv[1];
	}
	
	/*
		aca iria la ejecucion
	*/
	int nro = 2;
	Real realTest(nro);
	realTest.printReal();

	printDouble((double)nro);	

	return 0;
}


