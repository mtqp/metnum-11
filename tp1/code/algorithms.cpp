#include "algorithms.h"

Real Gregory(int t_digits, int cantIt, bool truncates){
	Real pi_par(t_digits,truncates);
	Real pi_impar(t_digits,truncates);
	
	Real _1(1,t_digits,truncates);
	Real _4(4,t_digits,truncates);
	
	ullInt acumDenominador;
	
	for(int i=0;i<cantIt;i+=2){
		acumDenominador = 2*i+1;
		Real denominador(acumDenominador, cantIt, truncates);
		pi_par = pi_par + (_1/denominador);
	}

	for(int i=1;i<cantIt;i+=2){
		acumDenominador = 2*i+1;
		Real denominador(acumDenominador, cantIt, truncates);
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

	Real _1103(1103,t_digits,truncates);
	Real _26390(26390,t_digits,truncates);
	Real _396(396,t_digits,truncates);
	
	for(int i=0;i<cantIt;i++){
		Real iReal(i,t_digits,truncates);

		ullInt factNumULL = fact(4*i);	//como calculamos fact de un real, existe eso? FEITO
		ullInt factDenULL = fact(i);

		Real factNum(factNumULL,t_digits,truncates);
		Real factDen(factDenULL,t_digits,truncates);
		
		Real rnum(t_digits,truncates);
		Real rden(t_digits,truncates);
		
		rnum = factNum * (_1103 + (_26390*iReal));
		rden = pot(factDen,4) * pot(_396,4*i);

		pi = pi + (rnum/rden);
	}

	Real 	  _1(1,t_digits,truncates);
	Real     _8(8,t_digits,truncates);
	Real _9801(9801,t_digits,truncates);

	pi = pi * (squareRoot(_8)/_9801);
	
	return _1/pi;
}

/*Real Ramanujan(int t_digits, int cantIt, bool truncates){
	Real pi(t_digits,truncates);
	
	for(int i=0;i<cantIt;i++){
		cout << "i " << i << endl;
		
		ullInt num = fact(4*i)* (1103+26390*i);
		cout << "num " << num << endl;
		
		cout << pow(fact(i),4) << endl << pow(396,4*i) << endl;
		ullInt den = pow(fact(i),4) * pow(396,4*i);
		cout << "den " << den << endl;
		
		Real rnum(num,t_digits,truncates);
		double num_double = rnum.convert();
		cout << "num_double " << num_double << endl;
		
		Real rden(den,t_digits,truncates);
		double den_double = rden.convert();
		cout << "dem_double " << den_double << endl;

		pi = pi + (rnum/rden);
	}

	Real 	  uno(1,t_digits,truncates);
	Real     ocho(8,t_digits,truncates);
	Real nueve801(9801,t_digits,truncates);

	pi = pi * (squareRoot(ocho)/nueve801);
	
	return uno/pi;
}*/




