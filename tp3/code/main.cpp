#include "curve.h"

int main(int argc, char** argv){
	
	if(argc<3){
		cout << "Error en el pasaje de parametros: debe especificar el nombre del archivo de entrada y el de salida" << endl;
		exit(0);
	}
	
	/******************************************************************/
	/***************************** Entrada ****************************/
	/******************************************************************/
	
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
	pair xy[n];
	for(int i=0; i<n; i++){
		in >> xy[i].first;
		in >> xy[i].second;
	}
		
	/* Ignoro la linea en blanco */
	in.ignore(0,'\n');
	
	/* Leo el punto proximo a la curva y su nueva posicion */
	pair ipoint;
	pair fpoint;
	in >> ipoint.first;
	in >> ipoint.second;
	in >> fpoint.first;
	in >> fpoint.second;
	
	in.close();
	
	/******************************************************************/
	/**************************** Programa ****************************/
	/******************************************************************/
	
	Parametrization param(n,xy,Chord_length);
	Curve curve(n,xy,param);
	curve.print();
	vector<pair> sampling(m);
	sampling = curve.sampling(m);
	
	/******************************************************************/
	/***************************** Salida *****************************/
	/******************************************************************/
	
	ofstream out(argv[2]);
	if(!out.is_open()) cout << "No se puedo abrir el archivo: " << argv[2] << endl;
	
	out << m << endl;
	
	for(int i=0; i<m; i++){
		out << sampling[i].first << " ";
		out << sampling[i].second << endl;
	}
	
	out << endl;
	
	out.close();
	
	return 0;
}
