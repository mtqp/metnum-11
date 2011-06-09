#ifndef __PARAMETRIZATION_H__
#define __PARAMETRIZATION_H__

#include "includes.h"

enum ParamType{
	Uniform,
	Chord_length,
	Centripetal
};

class Parametrization{
	public:
		Parametrization(uint n, pair* xy, ParamType type);
		~Parametrization();
		
		double* data();
		
	private:
		double dist(double x1, double y1, double x2, double y2);

		double* t;
};

#endif