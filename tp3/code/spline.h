#ifndef __SPLINE_H__
#define __SPLINE_H__

#include "parametrization.h"
#include "polynomial.h"

class Spline{
	public:
		Spline(uint n, vector<double> x, vector<double> f_x);
		Spline(const Spline& s);
		~Spline();
		
		double evaluate(double t);
		vector<pair> getControls();
		uint amountControls();
		Polynomial getPolynom(int control);

		void print(uint polynomial);			//imprime un polinomio
				
	private:
		uint amount_control;
		vector<double> x;
		vector<double> a;			//coeficientes independiente
		vector<double> b;			//coeficientes lineal
		vector<double> c;			//coeficientes cuadratico
		vector<double> d;			//coeficientes cubico
};

#endif
