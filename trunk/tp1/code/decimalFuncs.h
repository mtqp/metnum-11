#ifndef __DECIMALFUNCS_H__
#define __DECIMALFUNCS_H__

#include "includes.h"
#include "Real.h"

double intToDouble(ullInt value);
double charToDouble(char* value);

/*MATHS functions*/
class Real;
Real squareRoot(Real num);	
Real arctan(Real real, int cantIt);
Real pot(Real real, int exp);

#endif
