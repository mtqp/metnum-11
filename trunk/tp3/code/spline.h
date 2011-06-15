#ifndef __SPLINE_H__
#define __SPLINE_H__

#include "parametrization.h"
#include "polynomial.h"

class Spline{
	public:
		Spline(uint n, vector<double> x, vector<double> f_x);
		Spline(const Spline& s);
		~Spline();
		
		uint amountControls() const;
		vector<double> getParams() const;
		vector<pair> getControls() const;
		Polynomial getPolynom(int polIndex) const;
		double evaluate(double t) const;
		void print(uint polynomial) const;			//imprime un polinomio
				
	private:
		uint amount_control;
		vector<double> x;
		vector<double> a;			//coeficientes independiente
		vector<double> b;			//coeficientes lineal
		vector<double> c;			//coeficientes cuadratico
		vector<double> d;			//coeficientes cubico
};

#endif
