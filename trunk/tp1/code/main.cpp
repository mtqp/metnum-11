#include <cmath>
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "printFuncs.h"
#include "intFuncs.h"
#include "Real.h"

using namespace std;

#define it_default 10

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
	int nro = 1;
	Real realTest(nro,52,true);
	
	realTest.printReal();

	cout << endl;

	printDouble((double)nro);	

	return 0;
}


