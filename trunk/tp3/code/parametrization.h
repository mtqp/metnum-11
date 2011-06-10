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
		
		vector<double> data();
		
	private:
		double point_dist(double x1, double y1, double x2, double y2);
		double sum_all_dist(uint n, vector<pair> xy, bool centripetal);
		void uniform(uint n, vector<pair> xy);
		void non_uniform(uint n, vector<pair> xy, bool centripetal);
		
		double amount_control;
		vector<double> t;
};

#endif