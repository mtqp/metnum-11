#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include "includes.h"

/*
	los coeficientes para crear el polinomio se pasan al reves
	--> a0 + a1.x + a2.x^2 + ... + an. x^n
*/

class Polynomial
{
	public:
		Polynomial(const vector<double> coefs, uint order);
		~Polynomial();

		double evaluate(double x) const;
		Polynomial derive() const;

	private:
		uint _order;
		vector<double> _coefs;
};

#endif
