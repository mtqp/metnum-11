#include "decimalFuncs.h"

Real squareRoot(Real number){
	double num_double = number.convert();

	num_double = sqrt(num_double);
	
	number.save(num_double);
	
	return number;
}
	

Real arctan(Real real, int cantIt){
	Real resATAN_par(real.presicion(), real.truncate());
	Real resATAN_impar(real.presicion(), real.truncate());

	ullInt den;
	Real num(real.presicion(), real.truncate());

	for(int i=0; i<cantIt; i+=2){
		den = (2*i)+1;
		num = pot(real,den);

		Real acumDen(den, real.presicion(), real.truncate());
		
		resATAN_par = resATAN_par + (num / acumDen);
	}
	
	for(int i=1; i<cantIt; i+=2){
		den = (2*i)+1;
		num = pot(real,den);

		Real acumDen(den, real.presicion(), real.truncate());

		resATAN_impar = resATAN_impar + (num / acumDen);
	}
	
	return resATAN_par-resATAN_impar;
}

/*Exponenciación de reales*/
Real pot(Real real, int exp){
	double number = real.convert();
	double fresh  = number;
	
	if(exp == 0){
		real.save(1.0);
		return real;
	}
	
	if(exp==1){
		return real;
	}
	
	if(exp>0){
		for(int i=1;i<exp;i++){
			number *= fresh;
		}
	}
	else
	{
		for(int i=1;i<exp;i++){
			number /= fresh;
		}		
	}
	real.save(number);
	
	return real;
}

/*Exponenciación de doubles sin utilizar POW de C++*/
double doublePot(double num, int exp){
	if(exp == 0){
		return 1.0;
	}
	
	if(exp==1){
		return num;
	}

	double fresh = num;
	
	if(exp>0){
		for(int i=1;i<exp;i++){
			num *= fresh;
		}
	}
	else
	{
		for(int i=1;i<exp;i++){
			num /= fresh;
		}		
	}
	
	return num;
}

/*
	Funciones de reinterpretación de la información
*/

double intToDouble(ullInt value){
	return *(double*) &value;
}

double charToDouble(char* value){
	return *(double*) value;
}


