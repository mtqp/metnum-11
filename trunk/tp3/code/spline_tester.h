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
	
		bool matchPolynomials(pair xy, uint controlNumber);
		bool matchFirstDeriv(pair xy, uint controlNumber);
		bool matchSecondDeriv(pair xy, uint controlNumber);
};

#endif
