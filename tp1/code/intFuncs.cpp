#include "intFuncs.h"

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
