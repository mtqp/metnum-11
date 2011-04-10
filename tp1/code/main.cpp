#include "includes.h"
#include "printFuncs.h"
#include "intFuncs.h"
#include "Real.h"
#include "algorithms.h"

/*
	HAY QUE POR PARAMETRO DE ENTRADA ELEGIR EL ALGO???
	tener en cuenta que hasta ahora la implementacion que tiene no soporta x ejemplo
	(-1)*Real+...
*/

void usage();

int main(int argc, char** argv){
	int t_digits;	//se usa para el constructor del tipo de datos nuestro
	int  cantIt;
	bool truncate;

	switch(argc){
		case 2:
			t_digits = t_digits_default;
			cantIt   = it_default;
			truncate = truncate_default;
			break;
		case 3:
			t_digits = atoi(argv[2]);
			cantIt   = it_default;
			truncate = truncate_default;
			break;
		case 4:
			t_digits = atoi(argv[2]);
			cantIt   = atoi(argv[3]);
			truncate = truncate_default;
			break;
		case 5:
			t_digits = atoi(argv[2]);
			cantIt   = atoi(argv[3]);
			truncate = (bool) atoi(argv[4]);
			cout << "t_digits" << t_digits << "cantIt" << cantIt << "truncate" << truncate << endl;
			break;			
		default:
			usage();
			exit(0);
	}
	
//	cout.presicion(t_digits);
//	cout.precision(10);
	Real _396(396,52,true);
	
	cout << pot(_396,8) << " || " << pow(396,8) << endl;
	exit(0);

	switch(atoi(argv[1])){
		case 1:
			cout << "PI calculado con Gregory: " 	<< Gregory(t_digits, cantIt, truncate) << endl;
			break;
		case 2:
			cout << "PI calculado con Machin: " 	<< Machin(t_digits, cantIt, truncate) << endl;
			break;
		case 3:
			cout << "PI calculado con Ramanujan: " 	<< Ramanujan(t_digits, cantIt, truncate) << endl;
			break;
		case 4:
			cout << "PI calculado con Gregory: " 	<< Gregory(t_digits, cantIt, truncate) << endl;
			cout << "PI calculado con Machin: " 	<< Machin(t_digits, cantIt, truncate) << endl;
			cout << "PI calculado con Ramanujan: " 	<< Ramanujan(t_digits, cantIt, truncate) << endl;
			break;
		default:
			usage();
			exit(0);
	}
	
/*	t_digits = 52;
	truncate = true;
	
	Real uno(1,t_digits,truncate);	
	Real tres(3,t_digits,truncate);
	Real res(0,t_digits,truncate);
	Real n(0,t_digits,truncate);

	printDouble(15.0);

	res = uno/diez;
	*/
	/*
	uno.printReal();
	tres.printReal();
	res.printReal();
*/
	return 0;
}

void usage(){
	cout << "use: ./pi [metodo] [tdigitos] [cantidadIteraciones] [trunca?]" << endl;
	cout << "El parametro 'metodos' debe ser una de las siguientes opciones:" << endl;
	cout << "\t 1 para Gregory" << endl;
	cout << "\t 2 para Machin" << endl;
	cout << "\t 3 para Ramanujan" << endl;
	cout << "\t 4 para los tres algoritmos" << endl;
	cout << "Son opcionales los ultimos tres parametros" << endl;
}


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

