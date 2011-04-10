#ifndef __REAL_H__
#define	__REAL_H__

#include "includes.h"
#include "printFuncs.h"
#include "intFuncs.h"
#include "decimalFuncs.h"

using namespace std;

class Real {
	public:
		Real();
		Real(llInt value);
		Real(llInt value, int t_digits,bool truncates);
		Real(int t_digits, bool truncates);
		~Real();
		
		Real operator+ (const Real &a);
		Real operator* (const Real &a);
		Real operator- (const Real &a);
		Real operator/ (const Real &a);
		Real& operator= (const Real &a);
	
		void printReal();
		double convert() const;	
		void save(double value);

		int presicion() const;
		bool truncate() const;
		
		void filterPrecision();		//VA PRIVADA!

		friend ostream &operator<<(ostream &stream, Real r);
	private:
		//void filterPrecision();		
		void copyDoubleToArray(double number);
		void copyDoubleToArray(ullInt sign, ullInt exp, ullInt mantissa);
		void setMascara();
		ullInt getSign();
		ullInt getExp();
		ullInt getMantissa();
		ullInt getMascara() const;	
		void setReal(llInt,int,bool);

		bool _truncates;
		int _tdigits;
		char _real[8];
		char _mascaraTdigits[8];
		llInt _original;
	
};

#endif
