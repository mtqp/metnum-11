#include "curve.h"

int main(int argc, char** argv){
	
	if(argc<2){
		cout << "Error en el pasaje de parametros" << endl;
		exit(0);
	}
	
	/* Abro el archivo */
	ifstream in(argv[1]);
	if(!in.is_open()) cout << "No se puedo abrir el archivo: " << argv[1] << endl;
	
	/* Leo la cantidad de puntos de control */
	uint n;
	in >> n;
	
	/* Leo la cantidad de puntos de muestreo */
	uint m;
	in >> m;
	
	/* Leo los puntos de control (x,y) */
	double x[n];
	double y[n];
	for(int i=0; i<n; i++){
		in >> x[i];
		in >> y[i];
	}
		
	/* Ignoro la linea en blanco */
	in.ignore(0,'\n');
	
	/* Leo el punto proximo a la curva y su nueva posicion */
	pair<double, double> ipoint;
	pair<double, double> fpoint;
	in >> ipoint.first;
	in >> ipoint.second;
	in >> fpoint.first;
	in >> fpoint.second;
	
	Parametrization param(n,x,y,Chord_length);
	Curve curve(n,x,y,param);
	curve.print();
	
	return 0;
}
