#ifndef __CURVE_H__
#define __CURVE_H__

#include "spline.h"

class Curve{
	public:
		Curve(uint n, double* x, double* y, Parametrization t);
		~Curve();
		
		//funcion que modifique un punto
		void print();
		
	private:
		//funcion que busque el punto mas cercano perteneciente a la curva
		
		uint amount_control;
		Spline S_x;
		Spline S_y;
};

#endif
