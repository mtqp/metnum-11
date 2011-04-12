#ifndef __REAL_H__
#define	__REAL_H__

#include "includes.h"
#include "printFuncs.h"
#include "intFuncs.h"
#include "decimalFuncs.h"

using namespace std;

class Real {
	public:
		/*Constructores*/
		Real();
		Real(llInt value);
		Real(llInt value, int t_digits,bool truncates);
		Real(int t_digits, bool truncates);
		~Real();
		
		/*Operadores*/
		Real operator+ (const Real &a);
		Real operator* (const Real &a);
		Real operator- (const Real &a);
		Real operator/ (const Real &a);
		Real& operator= (const Real &a);
	
		/*Observadores*/
		int presicion() const;
		bool truncate() const;

		/*Otros*/	
		double convert() const;	
		void save(double value);
//		void save(ullInt sign, ullInt exp, ullInt mantissa);
		
		void filterPrecision();		//VA PRIVADA!

		/*Funciones Stream*/
		void printReal();
		void printRealBits();
		friend ostream &operator<<(ostream &stream, Real r);
	private:
		/*Ver data*/
		ullInt getMascara() const;
		int    getExp();	

		/*Set Data*/
		//void filterPrecision();		
		void copyDoubleToArray(double number);
		void copyDoubleToArray(ullInt sign, ullInt exp, ullInt mantissa);
		void setMascara();
		
		/*Iniciales*/
		void   setReal(llInt,int,bool);
		ullInt getInitSign();
		ullInt getInitExp();
		ullInt getInitMantissa();

		/*Data interna*/
		bool _truncates;
		int _tdigits;
		char _real[8];
		char _mascaraTdigits[8];
		llInt _original;
	
};

#endif
