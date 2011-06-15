#include "spline.h"

Spline :: Spline(uint n, vector<double> xs, vector<double> f_x) : x(n), a(n), b(n-1), c(n), d(n-1){
	amount_control = n;
	
	for(uint i=0; i<n; i++){
			x[i] = xs[i];
			a[i] = f_x[i];
	}
	
	vector<double> h(n-1);				//se interpreta desde cero (h_0, h_1, ..., h_n-1)
	vector<double> alpha(n-1);			//se interpreta desde uno (alpha_1, alpha_2, ..., alpha_n-2)
	
	for(uint i=0; i<n-1; i++){
		h[i] = x[i+1] - x[i];
		if(i!=0)
			alpha[i] = (3/h[i])*(a[i+1] - a[i]) - (3/h[i-1])*(a[i] - a[i-1]);
	}
	
	vector<double> l(n);
	vector<double> u(n-1);
	vector<double> z(n);
	
	l[0] = 1;
	u[0] = 0;
	z[0] = 0;
	
	for(uint j=1; j<n-1; j++){
			l[j] = 2*(x[j+1] - x[j-1]) - (h[j-1]*u[j-1]);
			u[j] = h[j]/l[j];
			z[j] = (alpha[j] - h[j-1]*z[j-1])/l[j];
	}
	
	l[n-1] = 1;
	z[n-1] = 0;
	c[n-1] = 0;
	
	for(int k=n-2; k>=0; k--){
		c[k] = z[k] - u[k]*c[k+1];
		b[k] = (a[k+1] - a[k])/h[k] - h[k]*(c[k+1] + 2*c[k])/3;
		d[k] = (c[k+1] - c[k])/(3*h[k]);
	}
}

Spline :: Spline(const Spline& s) : x(s.x), a(s.a), b(s.b), c(s.c), d(s.d) {
	this->amount_control = s.amount_control;
}

Spline :: ~Spline(){}

uint Spline :: amountControls() const{
	return amount_control;
}

vector<pair> Spline :: getControls() const{
	vector<pair> controls(amount_control);
	
	for(int i=0; i<amount_control; i++)
	{
		controls[i].first = x[i];
		controls[i].second= a[i];
	}
	
	return controls;
}

Polynomial Spline :: getPolynom(int polIndex) const{
	polIndex--;
	if(polIndex < 0 || polIndex > amount_control-1)
		cout << "No se puede obtener el polinomio pedido" << endl;
	
	int quantityCoefs = 4;
	
	vector<double> coefs(quantityCoefs);
	coefs[0] = a[polIndex];
	coefs[1] = b[polIndex];
	coefs[2] = c[polIndex];
	coefs[3] = d[polIndex];

	double xj = x[polIndex];

	Polynomial pol(coefs, xj,quantityCoefs-1);
	return pol;
}

double Spline :: evaluate(double t) const{
	uint i = 0;
	while(x[i+1] < t && i+1 < amount_control) i++;
	double h = (t - x[i]);
	return a[i] + b[i]*h + c[i]*h*h + d[i]*h*h*h;
}

void Spline :: print(uint polynomial) const{
	uint p = polynomial - 1;
	if(polynomial<=0 || polynomial>=amount_control)
		cout << "No existe tal polinomio " << endl;
	else{
		double x_ = x[p];
		cout << d[p] << "(x - " << x_ << ")^3 ";
		if(c[p]>=0) cout << "+ ";
		cout << c[p] << "(x - " << x_ << ")^2 ";
		if(b[p]>=0) cout << "+ ";
		cout << b[p] << "(x - " << x_ << ") ";
		if(a[p]>=0) cout << "+ ";
		cout << a[p] << endl;
	}
}
