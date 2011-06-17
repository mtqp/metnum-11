#ifndef __CURVE_H__
#define __CURVE_H__

#include "spline.h"

class Curve{
	public:
		Curve(uint n, vector<pair> xy, Parametrization t);
		Curve(uint n, vector<pair> xy, vector<double> t);
		Curve(const Curve& c);
		~Curve();

		Curve moveCurve(const pair fpoint, const pair ipoint) const;
		pair getNearPoint(const pair xy) const;

		vector<pair> sampling(uint m) const;						//intervalo [0,1]
		
		Curve& operator= (const Curve &c);
		void print() const;
		
	private:
		bool isControlPoint(double t, int& position) const;
		Curve moveControlPoint(const pair fpoint,int position) const;
		Curve movePoint(const pair fpoint, double t) const;
		double nearPoint(const pair xy) const;

		Polynomial distancePolynom(int polIndex,const pair xy, double t) const;
		uint amount_control;
		Spline* S_x;
		Spline* S_y;
};

#endif
