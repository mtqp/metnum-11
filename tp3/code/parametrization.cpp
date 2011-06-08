#include "parametrization.h"

Parametrization :: Parametrization(uint n, double* x, double* y, ParamType type){
	t = new double [n];
	switch(type){
		case(Uniform):
			cout << "Falta implementar" << endl;
			break;
		case(Chord_length):
			t[0]=0;
			for(int i=1; i<n; i++)
				t[i] = t[i-1] + dist(x[i-1], y[i-1], x[i], y[i]);
			break;
		case(Centripetal):
			cout << "Falta implementar" << endl;
			break;
	}
}

Parametrization :: ~Parametrization(){}

double* Parametrization :: data(){
	return t;
}

double Parametrization :: dist(double x1, double y1, double x2, double y2){
	double delta_x = x1 - x2;
	double delta_y = y1 - y2;
	
	delta_x *= delta_x;
	delta_y *= delta_y;
		
	return sqrt(delta_x + delta_y);
}