#include "decimalFuncs.h"

double intToDouble(ullInt value){
	return *(double*) &value;
}

double charToDouble(char* value){
	return *(double*) value;
}

Real squareRoot(Real number){
	double real = number.convert();

	real = sqrt(real);
	
	number.save(real);
	
	return number;
}
	

Real arctan(Real real, int cantIt){
	Real resATAN_par(real.presicion(), real.truncate());
	Real resATAN_impar(real.presicion(), real.truncate());

	ullInt den;

	for(int i=0; i<cantIt; i+=2){
		den = (2*i)+1;
		Real num(0, real.presicion(), real.truncate());
		num = pot(real,den);

		Real acumDen(den, real.presicion(), real.truncate());
		
		resATAN_par = resATAN_par + (num / acumDen);
	}
	
	for(int i=1; i<cantIt; i+=2){
		den = (2*i)+1;
		Real num(0, real.presicion(), real.truncate());
		num = pot(real,den);

		Real acumDen(den, real.presicion(), real.truncate());

		resATAN_impar = resATAN_impar + (num / acumDen);
	}
	
	return resATAN_par-resATAN_impar;
}


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
	
	for(int i=1;i<exp;i++){
		number *= fresh;
	}
	
	real.save(number);
	
	return real;
}



