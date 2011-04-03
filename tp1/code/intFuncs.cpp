#include "intFuncs.h"

/*
 * 	Funciones extras
 */

//no olvidarse de hacer un try catch para si hay overflow! asi lo podemos controlar...
ullInt fact(ullInt x){
	if(x != 0){
		ullInt i = x-1;
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

ullInt cleanSign(llInt number){
	if(number<0){
		number = number << 1;
		number = number >> 1;
	}

	return (ullInt) number;	
}


