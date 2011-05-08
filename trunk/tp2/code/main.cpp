#include <iostream>
#include <fstream>
#include "includes.h"
#include "structs.h"
#include "matrix.h"
#include "vector.h"
#include "warp_cannon.h"

using namespace std;

int main(int argc, char** argv){
	if(argc!=3 && argc!=5){
		cout << "Error en el pasaje de parámetros" << endl;
		exit(0);
	}
	
	/* Abro los archivos */
	ifstream position(argv[1]);
	ofstream out(argv[2]);
	
	if(position && out){					//da cero si hay algun error
		double tmp;							//variable de lectura, guarda los datos temporalmente
	
		uInt time;
		position >> time;					
		time++;								//turno actual = primer turno (si no es el primer turno se setea despues)
		
		uInt dimension;
		position >> dimension;
		
		/* Creo la estructura */
		warpData wd(dimension);
		
		/* Seteo nuestra posicion en la estructura */
		for(int i=1;i<=dimension;i++){
			position >> tmp;
			(wd.position).setValue(tmp,i);
		}
		
		/* Si no es el primer turno */
		if(argc==5){
			ifstream ultimo(argv[3]);
			
			ultimo >> time;
			time++;							//turno actual = ultimo turno + 1
			
			uInt aux;
			ultimo >> aux;
			if(aux!=dimension){
				cout << "Inconsistencia en la dimension de la matriz" << endl;
				exit(0);
			}
			
			/* Seteo en la estructura el vector a donde impacto el ataque del enemigo en el turno anterior*/
			for(int i=1;i<=dimension;i++){
				ultimo >> tmp;
				(wd.d).setValue(tmp,i);
			}
			
			/* Seteo en la estructura la matriz que uso el enemigo para atacar en el turno anterior*/
			for(int i=1;i<=dimension;i++)
				for(int j=1;j<=dimension;j++){
					ultimo >> tmp;
					(wd.A).setValue(tmp,i,j);
				}

			ultimo.close();
		}
		
		/* Seteo el turno actual en la estructura */
		wd.turn = time;
		wd.threshold = default_threshold;
		wd.failedAttack = false;			//por ahora lo seteo en falso pero vamos a tener que leerlo de algun lado
		
		/**************************************************************
		 * Falta leer de algun archivo temporal nuestro los 'd' 
		 * anteriores con el numero de condicion de 'A' y llenar el 
		 * vector 'previous'
		 * ************************************************************/
		
		out << time << endl;
		out << dimension << endl;
		
		/* Llamada a la funcion principal */
	}
	else
		cout << "Error al abrir los archivos";
	
	position.close();
	out.close();
	
	return 0;
}
