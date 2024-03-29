#include "intFuncs.h"

ullInt cleanSign(llInt number){
	if(number<0)
		number *= -1;

	return (ullInt) number;	
}

int placesToShift(ullInt number,int until){
	int places = 0;
	
	while(number!=until){
		if(number==0) break;	//si el until es un numero negavito, jamas lo encontraria
		
		number = number >> 1;
		places++;
	}
	
	return places;
}


//elimina el bit en la posicion SHIFT (es decir si estaba en 1, lo deja en 0, y si estaba en 0 tbm.
/*su uso es para eliminar el bit implicito de la mantissa*/
ullInt cleanFirstNotZero(ullInt number, int shift){
	if(shift>=0){
		number = number << 64-shift+1;
		number = number >> 64-shift+1;
	}
	else 
	{
		number = number >> 64-shift+1;
		number = number << 64-shift+1;
	}
	
	return number;
}

/*
	Funciones de reinterpretacion de la informacion
*/
ullInt doubleToInt(double value){
	return *(ullInt*) &value;
}

ullInt charToInt(char* value){
	return *(ullInt*) value;
}


