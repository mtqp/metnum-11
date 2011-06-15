#include "polynomial.h"

Polynomial :: Polynomial(const vector<double> coefs, double xj, uint order) : _coefs(order+1) {
	_order = order;
	_xj = xj;
	for(int i=0;i<order+1;i++)
		_coefs[i] = coefs[i];	
}

Polynomial :: ~Polynomial(){}

Polynomial& Polynomial :: operator= (const Polynomial &p)
{
	if(this!=&p){
		this->_order = p._order;
		this->_xj    = p._xj;
		this->_coefs = p._coefs;
	}
	return *this;
}

vector<double> Polynomial :: coefficients() const{
	return _coefs;
}

double Polynomial :: evaluate(double x) const{
	double evaluationResult = 0;
	for(int i=0;i<_order+1;i++)
		evaluationResult += _coefs[i]*pow(x-_xj,i);
	return evaluationResult;
}

Polynomial Polynomial :: derive() const{
	if(_order == 1){
		vector<double> c(1,0);	//==> esto hace lo que queremos????
		Polynomial zero(c,this->_xj,0);
		return zero;
	}

	int newQuantCoefs = this->_order;
	vector<double> derivedCoefs(newQuantCoefs);
	
	for(int i=0;i<newQuantCoefs;i++)
		derivedCoefs[i] = _coefs[i+1]*(i+1);

	Polynomial derived(derivedCoefs, this->_xj,this->_order-1);
	return derived;
}

double Polynomial :: zeros(double a, double b) const{
	if(evaluate(a) < EPSILON)
		return a;
	if(evaluate(b) < EPSILON)
		return b;
	if(changeSign(a,b))
		return bisection(a,b);

	return -1;	//--> nada sirve oh nou! --> implementar el iterativo re loco
}

double Polynomial :: newton(double p0, uint iter) const{
	uint i=1;
	Polynomial derivedPol = this->derive();
	double pi = p0 - this->evaluate(p0)/derivedPol.evaluate(p0);
	
	while(i<=iter && abs(pi-p0) > EPSILON){
		i++;
		p0 = pi;
		pi = p0 - this->evaluate(p0)/derivedPol.evaluate(p0);
	}
	if(i>iter) return pi;
	return -1;
}

double Polynomial :: bisection(double a, double b) const {
	double c = (a+b)/2;
	while(evaluate(c) < EPSILON){
		if(changeSign(a,c))
			b = c;
		else
			a = c;
		c = (a+b)/2;
	}
	return c;
}	

bool Polynomial :: changeSign(double a, double b) const {
	return (evaluate(a) < 0 && evaluate(b)>0) || (evaluate(a) > 0 && evaluate(b)<0);
}

void Polynomial :: print() const{
	for(int i=_order; i>=0; i--){
		if(_coefs[i]>=0 && i!=_order) cout << "+ ";
		cout << _coefs[i] << "(x-" << _xj << ")^" << i << " ";
	}
	cout << endl;
}
