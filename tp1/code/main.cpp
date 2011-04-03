#include "includes.h"
#include "printFuncs.h"
#include "intFuncs.h"
#include "Real.h"

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
	Real uno(nro,52,true);
	
	Real dos(2,3,true);
	
	/*xq tienen q estar hechos con el mismo constructor!!!!?????*/
	uno.printReal();
	dos.printReal();
	
	Real res(0,0,true);
	
	res = uno + dos;
	
	res.printReal();
/*	realTest.printReal();
	cout << endl;
	printDouble((double)nro);	*/

	return 0;
}


