#include "spline.h"
#include "spline_tester.h"
#include "polynomial.h"

int main(int argc, char** argv){
	
	if(argc<2){
		cout << "Error en el pasaje de parametros: debe especificar el nombre del archivo de entrada" << endl;
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
	
	/* Leo los puntos de control (x,y) */
	vector<double> x(n);
	vector<double> y(n);
	for(int i=0; i<n; i++){
		in >> x[i];
		in >> y[i];
	}
	
	in.close();
	
	/******************************************************************/
	/**************************** Programa ****************************/
	/******************************************************************/
/*	
	Spline s(n,x,y);
	for(int i=1; i<n; i++)
		s.print(i);
	SplineTester st(s);
	if(st.isSuccessful())
		cout << "OK!" << endl;
	else
		cout << "Error!" << endl;
*/	
	/******************************************************************/
	/*************************** Polinomio ****************************/
	/******************************************************************/
	
	
	
	
	return 0;
}
