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
		Parametrization(uint n, vector<pair> xy, ParamType type);
		~Parametrization();
		
		vector<double> data() const;
		
	private:
		double sumAllDist(uint n, vector<pair> xy, bool centripetal) const;
		void uniform(uint n);
		void nonUniform(uint n, vector<pair> xy, bool centripetal);
		
		double amount_control;
		vector<double> t;
};

#endif
