#include "intFuncs.h"

/*
 * 	Funciones extras
 */

//no olvidarse de hacer un try catch para si hay overflow! asi lo podemos controlar...
bestInt fact(bestInt x){
	if(x != 0){
		bestInt i = x-1;
		for(i;i!=0;i--){
			x *= i;
		}
		return x;		
	}
	else
	{
		return 1;
	}
}
