#include "algorithms.h"

Real Gregory(int t_digits, int cantIt, bool truncates){
	Real pi_par(t_digits,truncates);
	Real pi_impar(t_digits,truncates);
	
	Real uno(1,t_digits,truncates);
//	Real dos(2,t_digits,truncates);
	Real cuatro(4,t_digits,truncates);
	
	ullInt acumDenominador;
	
	/*tranquilamente podria pasarse antes de empezar todo a float y darle rosca, pero tendriamos mas error!*/
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

//	pi = pi_par-pi_impar;

	return (pi_par-pi_impar)*cuatro;
}

