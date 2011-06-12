#include "spline_tester.h"

SplineTester :: SplineTester(Spline s) : _spline(s) { }

SplineTester :: ~SplineTester() {}

bool SplineTester :: isSuccessful()
{
	bool success = true;
	
	vector<pair> controls = _spline.getControls();
	
	for(int ptoControl=1; ptoControl<=controls.size() && success; ptoControl++)
	{
		success &= matchPolynomials(controls[ptoControl-1],ptoControl);
		success &= matchFirstDeriv(controls[ptoControl-1], ptoControl);
		success &= matchSecondDeriv(controls[ptoControl-1], ptoControl);
	}
	
	return success;
}

bool SplineTester :: matchPolynomials(pair xy, uint controlNumber)
{
	bool isMatch = true;

	if(controlNumber == 1)
		//caso border primero
		return algo

	if(controlNumber == _spline.amountControls())
		//caso borde ultimo
		return algo
	
	Polynomial leftPol = _spline.getPolynom(controlNumber-1);
	Polynomial rightPol= _spline.getPolynom(controlNumber);
	
	double leftY = leftPol.evaluate(xy.first);
	double rightY= rightPol.evaluate(xy.first);
	
	return abs(leftY-xy.second) < EPSILON && abs(rightY-xy.second) < EPSILON;
}

bool SplineTester :: matchFirstDeriv(pair xy, uint controlNumber)
{
	bool isMatch = true;
	
	return isMatch;
}

bool SplineTester :: matchSecondDeriv(pair xy, uint controlNumber)
{
	bool isMatch = true;
	
	return isMatch;
}
