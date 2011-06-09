#ifndef __CURVE_H__
#define __CURVE_H__

#include "spline.h"

class Curve{
	public:
		Curve(uint n, pair* xy, Parametrization t);
		~Curve();
		
		//funcion que modifique un punto
		void print();
		vector<pair> sampling(uint m);						//intervalo [0,1]
		
	private:
		//funcion que busque el punto mas cercano perteneciente a la curva
		
		uint amount_control;
		Spline* S_x;
		Spline* S_y;
};

#endif
