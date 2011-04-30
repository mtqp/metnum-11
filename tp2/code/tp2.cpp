#include <iostream>
#include <fstream>
#include "includes.h"

using namespace std;

int main(int argc, char** argv){
	if(argc!=3 && argc!=5){
		cout << "Error en el pasaje de parámetros" << endl;
		exit(0);
	}
	
	/* Abro los archivos */
	ifstream posicion(argv[1]);
	ofstream salida(argv[2]);
	
	if(posicion && salida){					//da cero si hay algun error
		uInt time;
		posicion >> time;
		cout << time << endl;
		
		uInt dimension;
		posicion >> dimension;
		cout << dimension << endl;
		
		double position[dimension];
		forn(i,dimension){
			posicion >> position[i];
			cout << position[i] << endl;
		}
		
		/* Si no es el primer turno */
		if(argc==5){
			ifstream ultimo(argv[3]);
			ultimo >> time;
			cout << time << endl;
			ultimo.close();
		}
	}
	else
		cout << "Error al abrir los archivos"
	
	posicion.close();
	salida.close();
	
	return 0;
}
