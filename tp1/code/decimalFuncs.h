#ifndef __DECIMALFUNCS_H__
#define __DECIMALFUNCS_H__

#include "includes.h"

double convertToDouble(ullInt* value);
double intToDouble(ullInt value);
double charToDouble(char* value); //precond, levanto 8bytes... mas te vale tenerlo con datos veridicos

#endif
