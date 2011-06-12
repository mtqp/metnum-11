
#include "polynomial.h"

Polynomial :: Polynomial(const vector<double> coefs, uint order) : _coefs(order+1) {
	_order = order;
	for(int i=0;i<order+1;i++)
		_coefs[i] = coefs[i];	
}

Polynomial :: ~Polynomial() {}

double Polynomial :: evaluate(double x) const
{
	double evaluationResult = 0;
	for(int i=0;i<_order+1;i++)
		evaluationResult += _coefs[i]*pow(x,i);
	return evaluationResult;
}

Polynomial Polynomial :: derive() const
{
	if(_order == 1)	{	//resolver caso de cte!!!
		vector<double> c(1,0);	//==> esto hace lo que queremos????
		Polynomial zero(c,0);
		return zero;
	}

	int newQuantCoefs = this->_order;
	vector<double> derivedCoefs(newQuantCoefs);
	
	for(int i=0;i<newQuantCoefs;i++)
		derivedCoefs[i] = _coefs[i+1]*i+1;

	Polynomial derived(derivedCoefs, this->_order-1);
	return derived;
}

