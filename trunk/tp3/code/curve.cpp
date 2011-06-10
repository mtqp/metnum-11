#include "curve.h"

Curve :: Curve(uint n, vector<pair> xy, Parametrization t){
	amount_control = n;
	
	vector<double> x(n);
	vector<double> y(n);
	for(int i=0; i<n; i++){
		x[i] = xy[i].first;
		y[i] = xy[i].second;
	}
	
	S_x = new Spline(n,t.data(),x);
	S_y = new Spline(n,t.data(),y);
}

Curve :: ~Curve(){
	delete S_x;
	delete S_y;
}

vector<pair> Curve :: sampling(uint m){
	if(m<2) cout << "m debe ser mayor a 1 sino no se puede incluir a los extremos" << endl;
	vector<pair> sampling(m);
	double t_dist = 1.0/(m-1);
	double t = 0;
	for(int i=0; i<m; i++){
		sampling[i].first = (*S_x).evaluate(t);
		sampling[i].second = (*S_y).evaluate(t);
		t += t_dist;
	}
	return sampling;
}

void Curve :: print(){
	for(int i=1;i<amount_control;i++){
		cout << "S_x" << i << " = ";
		(*S_x).print(i);
	}
	for(int i=1;i<amount_control;i++){
		cout << "S_y" << i << " = ";
		(*S_y).print(i);
	}
}