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

/*hay que hacerle el complemento a dos*/
ullInt cleanSign(llInt number){
	if(number<0)
		number *= -1;

	return (ullInt) number;	
}

/*lo ponemos como unsigned int el until?*/
int placesToShift(ullInt number,int until){
	int places = 0;
	
	while(number!=until){
		number = number >> 1;
		places++;
	}
	
	return places;
}
