#include "includes.h"
#include "printFuncs.h"
#include "intFuncs.h"
#include "Real.h"
#include "algorithms.h"

/*
	tener en cuenta que hasta ahora la implementacion que tiene no soporta x ejemplo
	(-1)*Real+...
*/

void outThree(int tdigits, int cantIt, bool truncate);
void outGregory(int tdigits, int cantIt, bool truncate);
void outMachin(int tdigits, int cantIt, bool truncate);
void outRamanujan(int tdigits, int cantIt, bool truncate);
void usage();

int main(int argc, char** argv){
	int t_digits = 51;
	int  cantIt = 10;
	bool truncate = true;

	switch(argc){
		case 3:
			cout << "Uso de parametros por defecto: " << endl;
			cout << "\t tdigitos = " << t_digits << endl;
			cout << "\t cantidadIteraciones = " << cantIt << endl;
			cout << "\t trunca? = " << truncate << endl;
			break;
		case 4:
			t_digits = atoi(argv[3]);
			cout << "Uso de parametros por defecto: " << endl;
			cout << "\t cantidadIteraciones = " << cantIt << endl;
			cout << "\t trunca? = " << truncate << endl;
			break;
		case 5:
			t_digits = atoi(argv[3]);
			cantIt   = atoi(argv[4]);
			cout << "Uso de parametros por defecto: " << endl;
			cout << "\t trunca? = " << truncate << endl;
			break;
		case 6:		//wtf?
			t_digits = atoi(argv[3]);
			cantIt   = atoi(argv[4]);
			if (strcmp(argv[5],"-r")==0) truncate = 0;
			//cout << "tdigits " << t_digits << "cantIt " << cantIt << "truncate " << truncate << endl;
			break;
			t_digits = atoi(argv[2]);
			cantIt   = atoi(argv[3]);
			truncate = (bool) atoi(argv[4]);
			//cout << "t_digits" << t_digits << "cantIt" << cantIt << "truncate" << truncate << endl;
			break;
		default:
			usage();
			exit(0);
	}
	
	if(t_digits > 51 || (argc>=6 && strcmp(argv[5],"-t")!=0 && strcmp(argv[5],"-r")!=0) || (strcmp(argv[1],"-i")!=0 && strcmp(argv[1],"-terminos")!=0 && strcmp(argv[1],"-digitos")!=0)){
		usage();
		exit(0);
	}

	cout.precision(t_digits);
	switch(atoi(argv[2])){
		case 1:
			if(strcmp(argv[1],"-terminos")==0){
				for(int j=1; j<=t_digits; j++){
					cout.precision(j);
					outThree(j, cantIt, truncate);
				}
			}
			else{
				if(strcmp(argv[1],"-digitos")==0){
					for(int j=1; j<=cantIt; j++)
						outGregory(t_digits, j, truncate);
				}
				else 
					outGregory(t_digits, cantIt, truncate);
			}
			break;
		case 2:
			if(strcmp(argv[1],"-terminos")==0){
				for(int j=1; j<=t_digits; j++){
					cout.precision(j);
					outMachin(j, cantIt, truncate);
				}
			}
			else{
				if(strcmp(argv[1],"-digitos")==0){
					for(int j=1; j<=cantIt; j++)
						outMachin(t_digits, j, truncate);
				}
				else 
					outMachin(t_digits, cantIt, truncate);
			}
			break;
		case 3:
			if(strcmp(argv[1],"-terminos")==0){
				for(int j=1; j<=t_digits; j++){
					cout.precision(j);
					outRamanujan(j, cantIt, truncate);
				}
			}
			else{
				if(strcmp(argv[1],"-digitos")==0){
					for(int j=1; j<=cantIt; j++)
						outRamanujan(t_digits, j, truncate);
				}
				else 
					outRamanujan(t_digits, cantIt, truncate);
			}
			break;
		case 4:
			if(strcmp(argv[1],"-terminos")==0){
				for(int j=1; j<=t_digits; j++){
					cout.precision(j);
					outThree(j, cantIt, truncate);
					//outThree(t_digits, cantIt, truncate);
				}
			}
			else{
				if(strcmp(argv[1],"-digitos")==0){
					for(int j=1; j<=cantIt; j++){
						outThree(t_digits, j, truncate);
						//outThree(t_digits, cantIt, truncate);				
					}
				}
				else
					outThree(t_digits, cantIt, truncate);
			}
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

/*
	Extra funcs
*/

void outThree(int tdigits, int cantIt, bool truncate){
	outGregory(tdigits,cantIt,truncate);
	outMachin(tdigits,cantIt,truncate);
	outGregory(tdigits,cantIt,truncate);	
}

void outGregory(int tdigits, int cantIt, bool truncate){
	cout << "PI calculado con Gregory: " << Gregory(tdigits, cantIt, truncate) << endl;
}

void outMachin(int tdigits, int cantIt, bool truncate){
	cout << "PI calculado con Machin: " << Machin(tdigits, cantIt, truncate) << endl;
}

void outRamanujan(int tdigits, int cantIt, bool truncate){
	cout << "PI calculado con Ramanujan: " 	<< Ramanujan(tdigits, cantIt, truncate) << endl;
}

void usage(){
	cout << "uso: ./pi [modoUso] [metodo] [tdigitos] [cantidadIteraciones] [trunca?] \t(opcionales los ultimos tres parametros) " << endl;
	cout << endl;
	cout << "El parametro 'modoUso' debe ser una de las siguientes opciones:" << endl;
	cout << "\t -i  para ejecutar una instancia" << endl;
	cout << "\t -terminos para fijar la cantidad de terminos de la serie en 'cantidadIteraciones' y variar la precision hasta 'tdigitos'" << endl;
	cout << "\t -digitos para fijar la precision en 'tdigitos' y variar la cantidad de terminos de la serie hasta 'cantidadIteraciones'" << endl;
	cout << endl;
	cout << "El parametro 'metodos' debe ser una de las siguientes opciones:" << endl;
	cout << "\t 1 para Gregory" << endl;
	cout << "\t 2 para Machin" << endl;
	cout << "\t 3 para Ramanujan" << endl;
	cout << "\t 4 para los tres algoritmos" << endl;
	cout << endl;
	cout << "El parametro 'tdigitos' debe ser menor a 52" << endl;
	cout << endl;
	cout << "El parametro 'trunca?' se especifica de la siguiente manera:" << endl;
	cout << "\t -t para Truncar el resultado" << endl;
	cout << "\t -r para Redondear el resultado" << endl;
}


