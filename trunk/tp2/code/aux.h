#ifndef __AUX_H__
#define __AUX_H__

#include "includes.h"

template <typename T>
T module(T value){
	if(value<0)
		return (-1)*value;
	return value;
}

template <typename T>
T squareRoot(T value){
	double res = sqrt((double) value);
	return (T)res;	//T tiene q tener implementado el casteo a double.
}

#endif
