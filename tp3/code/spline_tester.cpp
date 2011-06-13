#include "spline_tester.h"

SplineTester :: SplineTester(Spline s) : _spline(s){}

SplineTester :: ~SplineTester(){}

bool SplineTester :: isSuccessful()
{
	vector<pair> controls = _spline.getControls();
	for(int i=0; i<controls.size(); i++)
		cout << "( " << controls[i].first << ", " << controls[i].second << " )" << endl;
	
	bool success = matchPolynomials(controls[0],1);								//--->caso 1er pto control
	success &= matchPolynomials(controls[controls.size()-1], controls.size()); 	//--->caso ultimo pto control
	
	for(int ptoControl=2; ptoControl<controls.size()-1 && success; ptoControl++)
	{
		success &= matchPolynomials(controls[ptoControl-1], ptoControl);
		success &= matchFirstDeriv(controls[ptoControl-1], ptoControl);
		success &= matchSecondDeriv(controls[ptoControl-1], ptoControl);
	}

	success &= checkNaturalSplineCondition(controls[0].first, controls[controls.size()-1].first, controls.size());
	
	return success;
}

bool SplineTester :: checkNaturalSplineCondition(double xleft, double xright, uint amount_controls)
{
	bool checksForCondition = abs(_spline.getPolynom(1).derive().derive().evaluate(xleft)) < EPSILON;
	checksForCondition &= abs(_spline.getPolynom(amount_controls).derive().derive().evaluate(xright)) < EPSILON;
	return  checksForCondition;
}

bool SplineTester :: matchPolynomials(pair xy, int controlNumber){
	if(controlNumber == 1 || controlNumber == _spline.amountControls())
		return matchBorderCase(xy,controlNumber,0);
	return matchNthDeriv(xy, controlNumber, 0);
}

bool SplineTester :: matchFirstDeriv(pair xy, int controlNumber){
	return matchNthDeriv(xy, controlNumber, 1);
}

bool SplineTester :: matchSecondDeriv(pair xy, int controlNumber){
	return matchNthDeriv(xy, controlNumber, 2);
}

bool SplineTester :: matchBorderCase(pair xy, int controlNumber, uint nthDeriv){
	int caseControlNumber = (controlNumber == 1) ? 1 : controlNumber-1;
	Polynomial casePolynomial = _spline.getPolynom(caseControlNumber);
	double evalPolynomial = casePolynomial.evaluate(xy.first);
	return abs(evalPolynomial-xy.second) < EPSILON;
}

bool SplineTester :: matchNthDeriv(pair xy, int controlNumber, uint nthDeriv){
	Polynomial rightPol= _spline.getPolynom(controlNumber);
	Polynomial leftPol = _spline.getPolynom(controlNumber-1);
	
	for(int i=1;i<=nthDeriv;i++){
		leftPol = leftPol.derive();
		rightPol= rightPol.derive();
	}
	double leftY = leftPol.evaluate(xy.first);
	double rightY= rightPol.evaluate(xy.first);
	
	if(nthDeriv != 0)
		return abs(leftY-rightY) < EPSILON;
	else
		return abs(leftY-xy.second) < EPSILON && abs(rightY-xy.second) < EPSILON;
}
