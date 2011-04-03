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
	Real menosuno(-1,52,true);
	Real dos(2,3,true);
	Real nueve(9,52,true);
	Real cuatro(4,52,true);
	Real cinco(5,52,true);
	Real uno(1,52,true);	
	Real tres(3,52,true);
//	nueve.squareRoot().printReal();
//	menosuno.squareRoot().printReal();

	Real res(0,0,true);
	//menosuno.printReal();
	//dos.printReal();
//	res = menosuno - dos; // =)
	res = uno/nueve;
//	res = res + tres;
	res.printReal();
	
	Real bla(12341,52,true);
	
	cout << uno << endl << bla << endl;
	cout << res << endl;
	
	/*xq tienen q estar hechos con el mismo constructor!!!!?????*/
/*	uno.printReal();
	dos.printReal();
	menosuno.printReal();
	tres.printReal();
	Real res(0,0,true);
	
	res = tres * menosuno;
	res.printReal();*/
/*	realTest.printReal();
	cout << endl;
	printDouble((double)nro);	*/

	return 0;
}


