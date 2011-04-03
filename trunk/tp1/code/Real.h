#ifndef __REAL_H__
#define	__REAL_H__

#include "includes.h"
#include "printFuncs.h"
#include "intFuncs.h"

using namespace std;

class Real {
	public:
		Real();
		Real(llInt value);
		Real(llInt value, int t_digits,bool truncates);
		Real(int t_digits, bool truncates);
		~Real();
		
		Real operator+ (const Real &a) const; //--> van a ser constantes o no? PENSAR
		Real operator* (const Real &a) const;
		Real operator- (const Real &a) const;
		Real operator/ (const Real &a) const;
		Real& operator= (const Real &a);
		Real squareRoot();
	
		void printReal();

	private:
		void copyDoubleToArray(double number);
		void copyDoubleToArray(ullInt sign, ullInt exp, ullInt mantissa);
		void setMascara();
		ullInt getSign();
		ullInt getExp();
		ullInt getMantissa();	
		double convert() const;
		bool _truncates;
		char _tdigits;
		char _real[8];
		char _mascaraTdigits[8];
		llInt _original;
	
};

#endif
