#include "algorithms.h"

Real Gregory(int t_digits, int cantIt, bool truncates){
	Real pi_par(t_digits,truncates);
	Real pi_impar(t_digits,truncates);
	
	Real uno(1,t_digits,truncates);
	Real cuatro(4,t_digits,truncates);
	
	ullInt acumDenominador;
	
	for(int i=0;i<cantIt;i+=2){
		acumDenominador = 2*i+1;
		Real denominador(acumDenominador, cantIt, truncates);
		pi_par = pi_par + (uno/denominador);
	}

	for(int i=1;i<cantIt;i+=2){
		acumDenominador = 2*i+1;
		Real denominador(acumDenominador, cantIt, truncates);
		pi_impar = pi_impar + (uno/denominador);
	}

	return (pi_par-pi_impar)*cuatro;
}

Real Machin(int t_digits, int cantIt, bool truncates){
	Real cuatro(4,t_digits, truncates);
	Real    uno(1,t_digits, truncates);
	Real  cinco(5,t_digits, truncates);
	Real  dos39(239,t_digits, truncates);

	return cuatro*((cuatro*arctan(uno/cinco,cantIt)) - arctan(uno/dos39,cantIt));
}

Real Ramanujan(int t_digits, int cantIt, bool truncates){
	Real pi(t_digits,truncates);
	
	for(int i=0;i<cantIt;i++){
		ullInt num = fact(4*i)* (1103+26390*i);	
		ullInt den = intPot(fact(i),4) * intPot(396,4*i);
		Real rnum(num,t_digits,truncates);

		pi = pi + (num/den);
	}

	Real 	  uno(1,t_digits,truncates);
	Real     ocho(8,t_digits,truncates);
	Real nueve801(9801,t_digits,truncates);

	pi = pi * (squareRoot(ocho)/nueve801);
	
	return uno/pi;
}

