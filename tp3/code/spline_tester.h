#ifndef __SPLINE_TESTER_H__
#define __SPLINE_TESTER_H__

#include "spline.h"

class SplineTester{
	public:
		SplineTester(Spline s);
		~SplineTester();

		bool isSuccessful();
	private:
		Spline _spline;
	
		bool matchPolynomials(pair xy, int controlNumber);
		bool matchFirstDeriv(pair xy, int controlNumber);
		bool matchSecondDeriv(pair xy, int controlNumber);
		bool matchNthDeriv(pair xy, int controlNumber, uint nthDeriv);
		bool matchBorderCase(pair xy, int controlNumber, uint nthDeriv);
		bool checkNaturalSplineCondition(double xleft, double xright, uint amount_controls);
};

#endif
