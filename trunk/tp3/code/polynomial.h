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

		double evaluate(double x) const;
		Polynomial derive() const;
		double getOneRoot(double a, double b);
	
		void print() const;

	private:
		double bisection(double a, double b);	//continua en el [a,b]
		bool changeSign(double a, double b);
	
		uint _order;
		double _xj;
		vector<double> _coefs;
};

#endif
