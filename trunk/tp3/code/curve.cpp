#include "curve.h"

Curve :: Curve(uint n, vector<pair> xy, Parametrization t){
	amount_control = n;
	
	param = t.data();
	
	vector<double> x(n);
	vector<double> y(n);
	for(int i=0; i<n; i++){
		x[i] = xy[i].first;
		y[i] = xy[i].second;
	}
	
	S_x = new Spline(n,param,x);
	S_y = new Spline(n,param,y);
}

Curve :: ~Curve(){
	delete S_x;
	delete S_y;
}
		
pair Curve :: nearPoint(pair xy) const{
	for(int i=1; i<amount_control; i++){
		Polynomial pol = distancePolynom(i,xy);
		pol.zeros(param[i-1],param[i]);
	}
}

vector<pair> Curve :: sampling(uint m) const{
	if(m<2) cout << "m debe ser mayor a 1 sino no se puede incluir a los extremos" << endl;
	vector<pair> sampling(m);
	double t_dist = 1.0/(m-1);
	double t = 0;
	for(int i=0; i<m; i++){
		sampling[i].first = S_x->evaluate(t);
		sampling[i].second = S_y->evaluate(t);
		t += t_dist;
	}
	return sampling;
}

Polynomial Curve :: distancePolynom(int polIndex,pair xy) const{
	
	/******************************************************************************************************
	 *  Distancia al cuadrado entre el polinomio 'polIndex' en x y el polinomio 'polIndex' en y al punto xy 
	 * (S_x(t) - x)^2 + (S_y(t) - y)^2
	 * Como busco minimizar esta funcion, derivo -->
	 * 2*(S_x(t) - x)*(S_x(t) - x)' + 2*(S_y(t) - y)*(S_y(t) - y)'
	 * reacomodando los terminos queda la expresion -->
	 * E_x + E_y donde E_x -->
	 * (llamamos z=(t-tj))
	 * 2bx(ax-x) + 2(bx^2+2cx(ax-x))*z + 6(cxbx+dx(ax-x)))*z^2 + 4(2dxbx+cx^2)*z^3 + 10dxcx*z^4 + 6dx^2*z^5
	 * Idem para E_y
	 * *****************************************************************************************************/
	
	Polynomial pol_x = S_x->getPolynom(polIndex);
	Polynomial pol_y = S_y->getPolynom(polIndex);
	
	vector<double> coefs_x(pol_x.coefficients());
	vector<double> coefs_y(pol_y.coefficients());
	
	//calculo ax-x
	double cte_x = coefs_x[0] - xy.first;
	double cte_y = coefs_y[0] - xy.second;
	
	vector<double> newCoefs(6);				//queda un polinomio de grado 5
	newCoefs[0] = 2*(coefs_x[1]*cte_x + coefs_y[1]*cte_y);
	newCoefs[1] = 2*((pow(coefs_x[1],2.0)+2*coefs_x[2]*cte_x) + (pow(coefs_y[1],2.0)+2*coefs_y[2]*cte_y));
	newCoefs[2] = 6*((coefs_x[2]*coefs_x[1] + coefs_x[3]*cte_x) + (coefs_y[2]*coefs_y[1] + coefs_y[3]*cte_y));
	newCoefs[3] = 4*((2*coefs_x[3]*coefs_x[1] + pow(coefs_x[2],2.0)) + (2*coefs_y[3]*coefs_y[1] + pow(coefs_y[2],2.0)));
	newCoefs[4] = 10*((coefs_x[3]*coefs_x[2]) + (coefs_y[3]*coefs_y[2]));
	newCoefs[5] = 6*((pow(coefs_x[3],2.0)) + (pow(coefs_y[3],2.0)));
	
	Polynomial newPol(newCoefs,param[polIndex-1],5);
	return newPol;
}

void Curve :: print() const{
	for(int i=1;i<amount_control;i++){
		cout << "S_x" << i << " = ";
		S_x->print(i);
	}
	for(int i=1;i<amount_control;i++){
		cout << "S_y" << i << " = ";
		S_y->print(i);
	}
}