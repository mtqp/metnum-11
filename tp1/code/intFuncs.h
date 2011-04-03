#ifndef _INTFUNCS_H_
#define _INTFUNCS_H_

#include "includes.h"

#define ullInt unsigned long long
#define llInt  long long

ullInt fact(ullInt x);
ullInt cleanSign(llInt number);
int placesToShift(ullInt number, int until);
#endif
