#ifndef __SPLINE_H__
#define __SPLINE_H__

#include "parametrization.h"

class Spline{
	public:
		Spline(uint n, double* x, double* f_x);
		~Spline();
		
		void print(uint polynomial);			//imprime un polinomio
		
	private:
		uint amount_control;
		double* x;
		double* a;			//coeficientes independiente
		double* b;			//coeficientes lineal
		double* c;			//coeficientes cuadratico
		double* d;			//coeficientes cubico
};

#endif
