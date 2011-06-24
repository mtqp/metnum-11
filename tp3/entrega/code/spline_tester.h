#ifndef __SPLINE_TESTER_H__
#define __SPLINE_TESTER_H__

#include "spline.h"

class SplineTester{
	public:
		SplineTester(Spline s);
		~SplineTester();

		bool isSuccessful() const;
	private:
		Spline _spline;
	
		bool matchPolynomials(pair xy, int controlNumber) const;
		bool matchFirstDeriv(pair xy, int controlNumber) const;
		bool matchSecondDeriv(pair xy, int controlNumber) const;
		bool matchNthDeriv(pair xy, int controlNumber, uint nthDeriv) const;
		bool matchBorderCase(pair xy, int controlNumber, uint nthDeriv) const;
		bool checkNaturalSplineCondition(double xleft, double xright, uint amount_controls) const;
};

#endif
