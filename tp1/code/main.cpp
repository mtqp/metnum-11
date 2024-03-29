#include "includes.h"
#include "printFuncs.h"
#include "intFuncs.h"
#include "Real.h"
#include "algorithms.h"

void out(SERIES*, char*, int, int, bool);
void checkForHelp(char** argv);
void usage();
void help();

bool eligeModoTruncamiento(int argc, char** argv);
bool eligeModoUso(char** argv);

Real PI(M_PI, 51, true);

int main(int argc, char** argv){
	int t_digits = 51;
	int  cantIt = 10;
	bool truncate = true;

	/*
	Real a(M_PI, 51, true);
	Real b((long long int)2, 51, true);
	
	cout << a-b << endl;

	return 0;*/
	if(argc<2){
		usage();
		exit(0);
	}
	else
	{
		if(!eligeModoUso(argv)){
			checkForHelp(argv);
			exit(0);
		}
	}
	
	switch(argc){
		case 2:
			checkForHelp(argv);
			break;
		case 3:
			cout << "Uso de parametros por defecto: " << endl;
			cout << "\t tdigitos = " << t_digits << endl;
			cout << "\t cantidadIteraciones = " << cantIt << endl;
			cout << "\t trunca? = " << truncate << endl;
			break;
		case 4:
			t_digits = (atoi(argv[3])<=51) ? atoi(argv[3]) : t_digits;
			cout << "Uso de parametros por defecto: " << endl;
			cout << "\t cantidadIteraciones = " << cantIt << endl;
			cout << "\t trunca? = " << truncate << endl;
			break;
		case 5:
			t_digits = (atoi(argv[3])<=51) ? atoi(argv[3]) : t_digits;
			cantIt   = atoi(argv[4]);
			cout << "Uso de parametros por defecto: " << endl;
			cout << "\t trunca? = " << truncate << endl;
			break;
		case 6:	
			t_digits = (atoi(argv[3])<=51) ? atoi(argv[3]) : t_digits;
			cantIt   = atoi(argv[4]);
			if(!eligeModoTruncamiento(argc,argv))
				if (strcmp(argv[5],"-r")==0) 
					truncate = false;
			break;
		default:
			usage();
			exit(0);
	}
	
	cout.precision(t_digits);
	switch(atoi(argv[2])){
		case 1:	
			out(&Gregory, argv[1], cantIt, t_digits, truncate);
			break;
		case 2:
			out(&Machin, argv[1], cantIt, t_digits, truncate);
			break;
		case 3:
			out(&Ramanujan, argv[1], cantIt, t_digits, truncate);
			break;
		case 4:
			out(&Gregory, argv[1], cantIt, t_digits, truncate);
			out(&Machin, argv[1], cantIt, t_digits, truncate);
			out(&Ramanujan, argv[1], cantIt, t_digits, truncate);
			break;
		default:
			usage();
			exit(0);
	}

	return 0;
}

/*
	Extra funcs
*/

void out(SERIES* funcion, char* arg, int cantIt, int t_digits, bool truncate){
	if(strcmp(arg,"-terminos")==0){
		for(int j=1; j<=t_digits; j++){
			cout.precision(j);
			cout << j << "\t" << (PI-funcion(j, cantIt, truncate))/PI << endl;
		}
	}
	else{
		if(strcmp(arg,"-digitos")==0){
			for(int j=1; j<=cantIt; j++){
				cout << j << "\t" << (PI-funcion(t_digits, j, truncate))/PI << endl;
			}
		}
		else{
			cout << (PI-funcion(t_digits, cantIt, truncate))/PI << endl;
		}
	}
}

bool eligeModoTruncamiento(int argc, char** argv){
	if(argc>=6)
		return strcmp(argv[5],"-t")!=0 || strcmp(argv[5],"-r")!=0;
	return false;
}

bool eligeModoUso(char** argv){
	return strcmp(argv[1],"-i")==0 || strcmp(argv[1],"-terminos")==0 || strcmp(argv[1],"-digitos")==0;
}

void checkForHelp(char** argv){
	if(strcmp(argv[1],"--help")==0)
		help();
	else
		usage();
}

void usage(){
	cout << "uso: ./pi [modoUso] [metodo] [tdigitos] [cantidadIteraciones] [trunca?]" << endl << "(opcionales los ultimos tres parametros) " << endl << endl;
	cout << "Para mas informacion usar ./pi --help" << endl << endl;
	cout << "El algoritmo de redondeo presenta inconsistencias, se les pide disculpas..." << endl;
}

void help(){
	cout << "uso: ./pi [modoUso] [metodo] [tdigitos] [cantidadIteraciones] [trunca?]" << endl << "(opcionales los ultimos tres parametros) " << endl << endl;
	cout << "----------" << endl;
	cout << "'modoUso':" << endl;
	cout << "\t -i  para ejecutar una instancia" << endl;
	cout << "\t -terminos para fijar la cantidad de terminos de la serie en 'cantidadIteraciones' y variar la precision hasta 'tdigitos'" << endl;
	cout << "\t -digitos para fijar la precision en 'tdigitos' y variar la cantidad de terminos de la serie hasta 'cantidadIteraciones'" << endl;
	cout << "----------" << endl;
	cout << "'metodos':" << endl;
	cout << "\t 1 para Gregory" << endl;
	cout << "\t 2 para Machin" << endl;
	cout << "\t 3 para Ramanujan" << endl;
	cout << "\t 4 para los tres algoritmos" << endl;
	cout << "----------" << endl;
	cout << "'tdigitos' debe ser menor a 52." << endl;
	cout << "----------" << endl;
	cout << "'trunca?':" << endl;
	cout << "\t -t para Truncar el resultado" << endl;
	cout << "\t -r para Redondear el resultado" << endl;
}
