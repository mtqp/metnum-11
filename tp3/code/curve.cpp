#include "curve.h"

Curve :: Curve(uint n, double* x, double* y, Parametrization t) : S_x(n,t.data(),x), S_y(n,t.data(),y){
	amount_control = n;
}

Curve :: ~Curve(){}

void Curve :: print(){
	for(int i=1;i<amount_control;i++){
		cout << "S_x" << i << " = ";
		S_x.print(i);
	}
	for(int i=1;i<amount_control;i++){
		cout << "S_y" << i << " = ";
		S_y.print(i);
	}
}