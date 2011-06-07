#ifndef __SPLINE_H__
#define __SPLINE_H__

#include "includes.h"

class Spline{
	public:
		Spline(uint n, double* x, double* f_x);
		~Spline();
		
		void print(uint polynomial);			//imprime un polinomio
		
		//funcion que modifique un punto
		
	private:
		//funcion que busque el punto mas cercano perteneciente a la curva
		uint amount_control;
		double* x;
		double* a;			//coeficientes independiente
		double* b;			//coeficientes lineal
		double* c;			//coeficientes cuadratico
		double* d;			//coeficientes cubico
};

#endif
