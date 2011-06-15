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
	vector<pair> xy(n);
	for(int i=0; i<n; i++){
		in >> xy[i].first;
		in >> xy[i].second;
	}
		
	/* Ignoro la linea en blanco */
	in.ignore(0,'\n');
	
	/* Leo el punto proximo a la curva */
	pair ipoint;
	in >> ipoint.first;
	in >> ipoint.second;
	
	/* Ignoro la linea en blanco */
	in.ignore(0,'\n');
	
	/* Leo la nueva posicion del punto */
	pair fpoint;
	in >> fpoint.first;
	in >> fpoint.second;
	
	in.close();
	
	/******************************************************************/
	/**************************** Programa ****************************/
	/******************************************************************/
	
	// Creo la parametrizacion y la curva
	Parametrization param(n,xy,Centripetal);
	Curve curve(n,xy,param);

	// Obtengo el muestreo de la spline original
	vector<pair> original_sampling(m);
	original_sampling = curve.sampling(m);
	
	// Muevo el punto
	pair near_point = curve.nearPoint(ipoint);	
	
	// Obtengo el muestreo de la spline deformada
	vector<pair> sampling(m);
	sampling = curve.sampling(m);
	

	/******************************************************************/
	/***************************** Salida *****************************/
	/******************************************************************/
	
	ofstream out(argv[2]);
	if(!out.is_open()) cout << "No se puedo abrir el archivo: " << argv[2] << endl;
	
	out << m << endl;
	
	for(int i=0; i<m; i++){
		out << original_sampling[i].first << " ";
		out << original_sampling[i].second << endl;
	}
	
	out << endl;
	
	out << near_point.first << " ";
	out << near_point.second << endl;
	
	out << endl;
	
	for(int i=0; i<m; i++){
		out << sampling[i].first << " ";
		out << sampling[i].second << endl;
	}
	
	out.close();
	
	return 0;
}
