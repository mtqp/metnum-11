#ifndef _INTFUNCS_H_
#define _INTFUNCS_H_

#include "includes.h"
#include "printFuncs.h"

#define ullInt unsigned long long
#define llInt  long long

ullInt cleanSign(llInt number);
ullInt cleanFirstNotZero(ullInt number, int shift);
int placesToShift(ullInt number, int until);
ullInt doubleToInt(double value);
ullInt charToInt(char* value);
//ullInt getRoundFactor(int places);

#endif
