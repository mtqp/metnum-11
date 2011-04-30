#include <iostream>
#include <fstream>
#include "includes.h"
#include "matrix_base.h"

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
		time++;								//turno actual, primer turno (si no es el primer turno se setea despues)
		cout << "time" << time << endl;
		
		uInt dimension;
		posicion >> dimension;
		cout << "dim " << dimension << endl;
		
		double position[dimension];
		forn(i,dimension){
			posicion >> position[i];
			cout << "pos " << position[i] << endl;
		}
		
		/* Si no es el primer turno */
		if(argc==5){
			ifstream ultimo(argv[3]);
			
			ultimo >> time;
			time++;							//turno actual, ultimo turno + 1
			cout << "time " << time << endl;
			
			uInt aux;
			ultimo >> aux;
			if(aux!=dimension){
				cout << "Inconsistencia en la dimension de la matriz" << endl;
				exit(0);
			}
			
			double d[dimension];
			forn(i,dimension){
				ultimo >> d[i];
				cout << "d " << d[i] << endl;
			}
			
			double elem;
			MatrixBase<double> A(dimension,dimension);
			forn(i,dimension)
				forn(j,dimension){
					ultimo >> elem;
					A.setValue(elem,i+1,j+1);
					cout << "A" << i+1 << j+1 << " " << A.getValue(i+1,j+1) << endl;
				}

			ultimo.close();
		}
		
		salida << time << endl;
		salida << dimension << endl;
		
		/* Llamada a la funcion principal */
		
		/* Guardar el vector y la matriz del turno actual */
	}
	else
		cout << "Error al abrir los archivos";
	
	posicion.close();
	salida.close();
	
	return 0;
}
