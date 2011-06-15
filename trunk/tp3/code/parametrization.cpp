#include "parametrization.h"

extern double pointDist(double x1, double y1, double x2, double y2);

Parametrization :: Parametrization(uint n, vector<pair> xy, ParamType type) : t(n){
	amount_control = n;
	switch(type){
		case(Uniform):
			uniform(n);
			break;
		case(Chord_length):
			nonUniform(n,xy,false);
			break;
		case(Centripetal):
			nonUniform(n,xy,true);
			break;
	}
}

Parametrization :: ~Parametrization(){}

vector<double> Parametrization :: data() const{
	return t;
}

double Parametrization :: sumAllDist(uint n, vector<pair> xy, bool centripetal) const{
	double sum = 0;
	for(int i=1; i<n; i++){
		sum += pow(pointDist(xy[i-1].first, xy[i-1].second, xy[i].first, xy[i].second),0.5*centripetal+!centripetal);
	}
	return sum;
}

void Parametrization :: uniform(uint n){
	double t_dist = 1.0/(n-1);
	t[0] = 0;
	for(int i=1; i<n; i++){
		t[i] = t[i-1] + t_dist;
	}
}

void Parametrization :: nonUniform(uint n, vector<pair> xy, bool centripetal){
	double total = sumAllDist(n,xy,centripetal);						//para mantenerme en el intervalo [0,1]
	double sum_acum = 0;												//para no tener que recalcular la suma
	t[0] = 0;
	for(int i=1; i<n; i++){
		sum_acum += pow(pointDist(xy[i-1].first, xy[i-1].second, xy[i].first, xy[i].second),0.5*centripetal+!centripetal);
		t[i] = sum_acum/total;
	}
}
