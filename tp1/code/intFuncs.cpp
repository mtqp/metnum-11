#include "intFuncs.h"

ullInt fact(ullInt x){
	if(x > 0){
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

ullInt intPot(ullInt number, int exp){
	if(exp==0)
		return 1ull;
	if(exp==1)
		return number;
	if(exp<0)
		return 0ull;
	else
	{
		ullInt freshNumber = number;
		for(exp;exp>1;exp--){
			number *= freshNumber;
		}
		return number;
	}

}

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

ullInt cleanFirstNotZero(ullInt number, int shift){
	number = number << 64-shift+1;
	number = number >> 64-shift+1;
	return number;
}

ullInt doubleToInt(double value){
	return *(ullInt*) &value;
}

ullInt charToInt(char* value){
	return *(ullInt*) value;
}

ullInt getRoundFactor(int places){	//QUIERO EVITAR USARLA!!!!!
	ullInt exp = 1020ull;		/*lo normaliza al desvio 1023*/
	ullInt roundFactor = 1ull;

	exp = exp << 52;
	roundFactor =  roundFactor << places;
	
	return exp | roundFactor;
}
