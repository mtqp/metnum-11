#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include "includes.h"

/*
	los coeficientes para crear el polinomio se pasan al reves
	--> a0 + a1.(x-xj) + a2.(x-xj)^2 + ... + an.(x-xj)^n
*/

class Polynomial
{
	public:
		Polynomial(const vector<double> coefs, double xj, uint order);
		~Polynomial();

		Polynomial& operator= (const Polynomial &p);

		vector<double> coefficients() const;
		double evaluate(const double x) const;
		Polynomial derive() const;
		double zeros(double a, double b) const;
		void print() const;

	private:
		double newton(double p0, double tolerance, llint iter) const;
		double bisection(double a, double b, double radius) const;	//continua en el [a,b]
		bool changeSign(const double a, const double b) const;
	
		uint _order;
		double _xj;
		vector<double> _coefs;
};

#endif
