#ifndef __SETP_POLYNOMIAL_H__
#define __SETP_POLYNOMIAL_H__

#include "includes.h"

/*
	los coeficientes para crear el polinomio se pasan al reves
	--> a0 + a1.(x-xj) + a2.(x-xj)^2 + ... + an.(x-xj)^n
*/

class Setp_Polynomial
{
	public:
		Setp_Polynomial(const vector<double> coefs, double xj, uint order);
		~Setp_Polynomial();

		double evaluate(const double x);
		Setp_Polynomial derive();
		vector<double> zeros(double a, double b, double tolerance, llint iter);
		
		ull getAmountOp() const;

	private:
		double newton(double p0, double tolerance, llint iter);
		double findRoot(double a, double b, double tolerance, llint iter);
	
		uint _order;
		double _xj;
		vector<double> _coefs;
		
		/* Contador de la cantidad de operaciones */
		ull amount_op;
};

#endif
