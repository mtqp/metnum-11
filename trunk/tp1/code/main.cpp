#include "includes.h"
#include "printFuncs.h"
#include "intFuncs.h"
#include "Real.h"

/*
	tener en cuenta que hasta ahora la implementacion que tiene no soporta x ejemplo
	(-1)*Real+...
*/

int main(int argc, char** argv){
	int t_digitos;	//se usa para el constructor del tipo de datos nuestro
	int  cantIteraciones;
	bool truncate;
	int i = 0;
		
	if(argc<2){
		cout << "use: ./errores [tdigitos] [cantidadIteraciones] [trunca?]" << endl;
		cout << "	Son opcionales los ultimos dos parametros??¿?¿?" << endl;
		return 0;
	}
	else 
	{
		//chequear aca el tercer parametro! es el bool de si trunca o no
		if(argc==2){
			cantIteraciones = it_default;
		}
		else
		{ 
			cantIteraciones = atoi(argv[2]);
		}
		
		t_digitos = atoi(argv[1]);
	}
	
	/*
		aca iria la ejecucion
	*/

	truncate = false;
/*	
	for(int i=0;i<cantIteraciones;i++){
		Real r(i,t_digitos,truncate);
		Real r2(i+1,t_digitos,truncate);
		Real mUno(-1,t_digitos,truncate);
		Real dos(2,t_digitos,truncate);
		res = mUno*(mUno*r+dos*r2);
//		res = mUno*r;
//		res = res + r2;
		cout << i << " --> " << res << endl;
	}
*/

	Real uno(1,t_digitos,truncate);	
	Real tres(3,t_digitos,truncate);
	Real res(0,t_digitos,truncate);

	res = uno / tres;
	
/*	uno.printReal();
	tres.printReal();
	res.printReal();
*/
/*
	PRUEBAS VIEJAS
*/
/*	int nro = 1;
	Real menosuno(-1,52,true);
	Real dos(2,3,true);
	Real nueve(9,52,true);
	Real cuatro(4,52,true);
	Real cinco(5,52,true);
	Real uno(1,52,true);	
	Real tres(3,52,true);
	nueve.squareRoot().printReal();
	menosuno.squareRoot().printReal();

	Real res(0,0,true);
	//menosuno.printReal();
	//dos.printReal();
	res = menosuno - dos; // =)
	res = uno/nueve;
	res = res + tres;
	res.printReal();
	
	Real bla(12341,52,true);
	
	cout << uno << endl << bla << endl;
	cout << res << endl;
	

	uno.printReal();
	dos.printReal();
	menosuno.printReal();
	tres.printReal();
	Real res(0,0,true);
	
	res = tres * menosuno;
	res.printReal();
	realTest.printReal();
	cout << endl;
	printDouble((double)nro);	
*/
	return 0;
}


