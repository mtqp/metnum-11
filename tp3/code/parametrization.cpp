#include "parametrization.h"

Parametrization :: Parametrization(uint n, vector<pair> xy, ParamType type) : t(n){
	amount_control = n;
	switch(type){
		case(Uniform):
			uniform(n,xy);
			break;
		case(Chord_length):
			non_uniform(n,xy,false);
			break;
		case(Centripetal):
			non_uniform(n,xy,true);
			break;
	}
}

Parametrization :: ~Parametrization(){}

vector<double> Parametrization :: data(){
	return t;
}

double Parametrization :: point_dist(double x1, double y1, double x2, double y2){
	double delta_x = x1 - x2;
	double delta_y = y1 - y2;
	
	delta_x *= delta_x;
	delta_y *= delta_y;
		
	return sqrt(delta_x + delta_y);
}

double Parametrization :: sum_all_dist(uint n, vector<pair> xy, bool centripetal){
	double sum = 0;
	for(int i=1; i<n; i++){
		sum += pow(point_dist(xy[i-1].first, xy[i-1].second, xy[i].first, xy[i].second),0.5*centripetal+!centripetal);
	}
	return sum;
}

void Parametrization :: uniform(uint n, vector<pair> xy){
	double t_dist = 1.0/(n-1);
	t[0] = 0;
	for(int i=1; i<n; i++){
		t[i] = t[i-1] + t_dist;
	}
}

void Parametrization :: non_uniform(uint n, vector<pair> xy, bool centripetal){
	double total = sum_all_dist(n,xy,centripetal);						//para mantenerme en el intervalo [0,1]
	double sum_acum = 0;												//para no tener que recalcular la suma
	t[0] = 0;
	for(int i=1; i<n; i++){
		sum_acum += pow(point_dist(xy[i-1].first, xy[i-1].second, xy[i].first, xy[i].second),0.5*centripetal+!centripetal);
		t[i] = sum_acum/total;
	}
}