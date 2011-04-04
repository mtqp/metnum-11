#include "decimalFuncs.h"

double intToDouble(ullInt value){
	return *(double*) &value;
}

double charToDouble(char* value){
	return *(double*) value;
}
