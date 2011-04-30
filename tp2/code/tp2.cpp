#include <iostream>
#include "includes.h"

using namespace std;

int main(int argc, char** argv){
	if(argc!=3 && argc!=5){
		cout << "Error en el pasaje de parámetros" << endl;
		exit(0);
	}
	
	/* Leo el archivo posicion */
	uInt time;
	cin >> time;
	
	uInt dimension;
	cin >> dimension;
	
	double position[dimension];
	forn(i,dimension)
		cin >> position[i];
		
	/* Si no es el primer turno */
	if(argc==5)
		cin >> time;
		
	return 0;
}
