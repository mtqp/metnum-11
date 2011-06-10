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

Spline :: ~Spline(){}

double Spline :: evaluate(double t){
	uint i = 0;
	while(x[i+1] < t && i+1 < amount_control) i++;
	double h = (t - x[i]);
	return a[i] + b[i]*h + c[i]*h*h + d[i]*h*h*h;
}

void Spline :: print(uint polynomial){
	uint p = polynomial - 1;
	if(polynomial<=0 || polynomial>=amount_control)
		cout << "No existe tal polinomio " << endl;
	else{
		double x_ = x[p];
		cout << d[p] << "(x - " << x_ << ")^3 + " << c[p] << "(x - " << x_ << ")^2 + " << b[p] << "(x - " << x_ << ") + " << a[p] << endl;
	}
}