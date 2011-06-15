#ifndef __CURVE_H__
#define __CURVE_H__

#include "spline.h"

class Curve{
	public:
		Curve(uint n, vector<pair> xy, Parametrization t);
		~Curve();
		
		pair nearPoint(pair xy) const;
		vector<pair> sampling(uint m) const;						//intervalo [0,1]
		void print() const;
	private:
		//funcion que busque el punto mas cercano perteneciente a la curva
		Polynomial distancePolynom(int polIndex,pair xy) const;
		uint amount_control;
		vector<double> param;
		Spline* S_x;
		Spline* S_y;
};

#endif
