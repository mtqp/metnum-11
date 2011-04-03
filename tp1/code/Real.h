#ifndef __REAL_H__
#define	__REAL_H__

#define ullInt unsigned long long
#define llInt  long long

#include <cstring>
#include "printFuncs.h"
#include "intFuncs.h"

using namespace std;

class Real {
	public:
		Real();
		Real(llInt value);
		Real(llInt value, int t_digits,bool truncates);
		~Real();
		
		Real operator+ (Real a); //--> van a ser constantes o no? PENSAR
		Real operator* (Real a);
		Real operator- (Real a);
//		Real operator/ (Real a, Real b);
//		Real operator= (Real a);
//		Real operator= (ullInt a);
		Real raizCuad();
	
		void printReal();
	
	private:
		void copyDoubleToArray(ullInt sign, ullInt exp, ullInt mantissa);
		ullInt getSign();
		ullInt getExp();
		ullInt getMantissa();	
		double convert();
		bool _truncates;
		char _tdigits;
		char _real[8];
		llInt _original;
	
};

#endif
