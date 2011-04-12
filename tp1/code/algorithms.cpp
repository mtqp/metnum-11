#include "algorithms.h"

Real Gregory(int t_digits, int cantIt, bool truncates){
	Real pi_par(t_digits,truncates);
	Real pi_impar(t_digits,truncates);
	
	Real _1(1,t_digits,truncates);	
	Real _4(4,t_digits,truncates);

	
	ullInt acumDenominador;
	
	for(int i=0;i<cantIt;i+=2){
		acumDenominador = 2*i+1;
		Real denominador(acumDenominador, t_digits, truncates);
		pi_par = pi_par + (_1/denominador);
	}

	for(int i=1;i<cantIt;i+=2){
		acumDenominador = 2*i+1;
		Real denominador(acumDenominador, t_digits, truncates);
		pi_impar = pi_impar + (_1/denominador);
	}

	return (pi_par-pi_impar)*_4;
}

Real Machin(int t_digits, int cantIt, bool truncates){
	Real _4(4,t_digits, truncates);
	Real _1(1,t_digits, truncates);
	Real _5(5,t_digits, truncates);
	Real _239(239,t_digits, truncates);

	return _4*((_4*arctan(_1/_5,cantIt)) - arctan(_1/_239,cantIt));
}

Real Ramanujan(int t_digits, int cantIt, bool truncates){
	Real pi(t_digits,truncates);

	Real _1(1,t_digits,truncates);
	Real _2(2,t_digits,truncates);
	Real _3(3,t_digits,truncates);
	Real _1103(1103,t_digits,truncates);
	Real _396(396,t_digits,truncates);
	Real fact_4n(1,t_digits,truncates);
	Real fact_n(1,t_digits,truncates);
	
	for(int i=1;i<cantIt;i++){
		ullInt factNumULL = 4*i;
		Real factNum(factNumULL,t_digits,truncates);
	
		//Calculo de (4i)! a partir de la iteracion anterior (4*(i-1))!
		fact_4n = fact_4n*(factNum*((factNum-_1)*((factNum-_2)*(factNum-_3))));
		
		ullInt numULL = (1103+26390*i);
		Real num(numULL,t_digits,truncates);
		
		Real rnum(t_digits,truncates);
		rnum = fact_4n*num;
		
		Real _i(i,t_digits,truncates);
		fact_n = fact_n*_i;
	
		Real rden(t_digits,truncates);
		rden = pot(fact_n,4) * pot(_396,4*i);
		
		pi = pi + (rnum/rden);
	}
	
	//Suma del primer termino de la serie
	pi = pi + _1103;

	Real _8(8,t_digits,truncates);
	Real _9801(9801,t_digits,truncates);

	pi = pi * (squareRoot(_8)/_9801);
	
	return _1/pi;
}




