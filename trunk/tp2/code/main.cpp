#include <iostream>
#include <fstream>
#include "includes.h"
#include "structs.h"
#include "matrix.h"
#include "vector.h"
#include "warp_cannon.h"

using namespace std;

int main(int argc, char** argv){
	srand(time(NULL));	//POR FAVOR NO BORRAR, ES PARA Q ANDE EL GENERADOR DE BADK'S
	
	if(argc!=3 && argc!=5){
		cout << "Error en el pasaje de parámetros" << endl;
		exit(0);
	}
	
	/* Abro los archivos */
	ifstream position(argv[1]);
	if(!position.is_open()) cout << "No se puedo abrir el archivo: " << argv[1] << endl;
	
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
		wd.position.setValue(tmp,i);
	}
	
	position.close();
	
	/* Si no es el primer turno */
	if(argc==5){
		ifstream ultimo(argv[3]);
		if(!ultimo.is_open()) cout << "No se puedo abrir el archivo: " << argv[3] << endl;
		
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
			wd.d.setValue(tmp,i);
		}
		
		/* Seteo en la estructura la matriz que uso el enemigo para atacar en el turno anterior*/
		for(int i=1;i<=dimension;i++)
			for(int j=1;j<=dimension;j++){
				ultimo >> tmp;
				wd.A.setValue(tmp,i,j);
			}

		ultimo.close();
	}
	
	/* Seteo el turno actual, el umbral y si fallamos en el ataque en la estructura */
	wd.turn = time;
	wd.threshold = default_threshold;
	
	/* Leo los datos de las posiciones del enemigo calculadas anteriormente */
	fstream position_enemy("posicion_enemiga", ios_base::in | ios_base::out);
	if(!position_enemy.is_open()) cout << "No se puedo abrir el archivo 'position_enemy'" << endl;
	
	uInt data_amount = time/2; 
	wd.position_enemy = new pair<Vector<double>*,double> [data_amount];			//creo uno de mas para el ataque recibido del turno anterior
	
	/* Voy a cagar solo los que tengo en el archivo, que no incluyen al ultimo ataque recibido */
	for(int i=0; i<data_amount-1; i++){
		wd.position_enemy[i].first = new Vector<double>(dimension);
		for(int j=1; j<=dimension+1; j++){
			position_enemy >> tmp;
			if(j!=dimension+1)
				(*wd.position_enemy[i].first).setValue(tmp,j);
			else
				wd.position_enemy[i].second = tmp;
		}
		cout << endl;
	}
	
	double cond_number = wd.A.K();
	
	/* Seteo el punto donde impacto el ultimo ataque recibido */
    wd.position_enemy[data_amount-1].first = new Vector<double>(wd.d);
    wd.position_enemy[data_amount-1].second = cond_number;
	
	/* Me posiciono al final del archivo */
	position_enemy.seekp(0,ios_base::end);
	
	/* Guardo en el archivo el punto donde impacto el ultimo ataque recibido */
	for(int j=1; j<=dimension+1; j++){
		if(j!=dimension+1){
			position_enemy << wd.d.getValue(j) << " ";
		}
		else{
			position_enemy << cond_number << endl;
		}
	}
	
	position_enemy.close();
	
	ofstream out(argv[2]);
	if(!out.is_open()) cout << "No se puedo abrir el archivo: " << argv[2] << endl;
	out << time << endl;
	out << dimension << endl;
	
	/* Llamada a la funcion principal */
	
	
	WarpCannon wp(wd,dimension);
	attackData wa(dimension);
	wa = wp.attack();

	/* Guardo en el archivo de salida el vector y la matriz */
	for(int i=1; i<=dimension; i++)
		out << wa.d.getValue(i) << " ";
	out << endl;
	
	for(int i=1; i<=dimension; i++){
		for(int j=1; j<=dimension; j++)
			out << wa.A.getValue(i,j) << " ";
		out << endl;
	}
	
	
	out.close();
	
	return 0;
}
