#include "setp_polynomial.h"

#define O(n) amount_op+=(n)

Setp_Polynomial :: Setp_Polynomial(const vector<double> coefs, double xj, uint order) : _coefs(order+1) {
	_order = order;
	_xj = xj;
	amount_op = 0;
	O(4);
	for(int i=0;i<order+1;i++){
		_coefs[i] = coefs[i];
		O(5);
	}
}

Setp_Polynomial :: ~Setp_Polynomial(){}

double Setp_Polynomial :: evaluate(const double x){
	double evaluationResult = 0;
	O(2);
	for(int i=0;i<_order+1;i++){
		evaluationResult += _coefs[i]*pow(x-_xj,i);
		O(9);
	}
	return evaluationResult;
}

Setp_Polynomial Setp_Polynomial :: derive(){
	if(_order == 1){
		vector<double> c(1,0);
		O(2);
		Setp_Polynomial zero(c,this->_xj,0);
		return zero;
	}

	int newQuantCoefs = this->_order;
	vector<double> derivedCoefs(newQuantCoefs);
	O(4);
	
	for(int i=0;i<newQuantCoefs;i++){
		derivedCoefs[i] = _coefs[i+1]*(i+1);
		O(8);
	}

	Setp_Polynomial derived(derivedCoefs, this->_xj,this->_order-1);
	return derived;
}

vector<double> Setp_Polynomial :: zeros(double a, double b, double tolerance, llint iter){
	int rootcount = _order;
	double interval = (b-a)/rootcount;
	double x = a;
	double x1= a+interval;
	vector<double> roots(rootcount);
	O(9);
	for(int i=0;i<rootcount;i++){
		roots[i] = findRoot(x, x1, tolerance, iter);
		x=x1;
		x1+=interval;
		O(7);
	}
	return roots;
}

double Setp_Polynomial :: findRoot(double a, double b, double tolerance, llint iter){
	if(abs(evaluate(a)) < EPSILON){
		O(2);
		return a;
	}
	if(abs(evaluate(b)) < EPSILON){
		O(4);
		return b;
	}
	O(6);
	return newton((a+b)/2,tolerance,iter);
}

double Setp_Polynomial :: newton(double p0, double tolerance, llint iter){
	llint i=1;
	Setp_Polynomial derivedPol = this->derive();
	double pi = p0 - this->evaluate(p0)/derivedPol.evaluate(p0);
	O(5);
	while(i<=iter && abs(pi-p0) > tolerance){
	//while(i<=iter){//para ajuste cantidad de iteraciones
		i++;
		p0 = pi;
		pi = p0 - this->evaluate(p0)/derivedPol.evaluate(p0);
		O(6);
	}
	return pi;
}

ull Setp_Polynomial :: getAmountOp() const{
	return amount_op;
}