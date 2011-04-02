#include <cmath>
#include <iostream>
//#include <string>
#include <cstdlib>
#include <cstdio>

//#define big_mathLib float
#define big_mathLib double
//#define big_mathLib long double
#define int_mathLib unsigned long long

#include "Real.h"

using namespace std;

#define bestInt int

bestInt fact(bestInt x){
	if(x != 0){
		bestInt i = x-1;
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


big_mathLib arctan(big_mathLib f, int cantIteraciones){
	big_mathLib resArc_par = 0;
	big_mathLib resArc_impar = 0;

	for(int i=0; i<cantIteraciones; i+=2){
		resArc_par += pow(f,2*i+1) / (2*i+1);
	}
	
	for(int i=1; i<cantIteraciones; i+=2){
		resArc_impar += pow(f,2*i+1) / (2*i+1);
	}
	
	resArc_par-resArc_impar;
	
	return resArc_par-resArc_impar;
}


big_mathLib Gregory(int cantIteraciones){
	big_mathLib pi_par=0;
	big_mathLib pi_impar=0;
	
	for(int i=0;i<cantIteraciones;i+=2){
		pi_par += 1.0/(2*i+1);
	}

	for(int i=1;i<cantIteraciones;i+=2){
		pi_impar += 1.0/(2*i+1);
	}

	big_mathLib pi=pi_par-pi_impar;

	return pi*4;
}

big_mathLib Machin(int cantIteraciones){
	big_mathLib pi = 4*arctan(1.0/5.0,cantIteraciones) - arctan(1.0/239.0,cantIteraciones);
	return pi*4;
}

big_mathLib Ramanujan(int cantIteraciones){
	big_mathLib pi=0;;
	
	for(int i=0;i<cantIteraciones;i++){
		pi += (fact(4*i) * (1103+26390*i))/(pow(fact(i),4) * pow(396,4*i));
	}

	pi *= sqrt(8)/9801;
	
	return 1/pi;
}

int main(int argc, char** argv){
	int t;	//se usa para el constructor del tipo de datos nuestro
	int cantIteraciones;
	int i = 1;
	
	/*hacer el parser lindo!*/
	if (argc>=2){
		cantIteraciones = atoi(argv[1]);
	} 
	else 
	{
		cantIteraciones = 10;			/*elegir dsp valor por defecto*/
	}
	
	//big_mathLib pi = Gregory(cantIteraciones);

	while(i < cantIteraciones){
		big_mathLib piGreg = Gregory(i);
		big_mathLib piMac  = Machin(i);
		big_mathLib piRam  = Ramanujan(i);
		
//		cout.precision(60);
//		cout << M_PI << endl;
		cout << "G_" << piGreg  << "|\tM_" << piMac << "|\tR_" << piRam << endl;
//		printf("G_%lf |\tM_%lf \tR_%lf\n",piGreg,piMac,piRam);
		i++;
	}

	return 0;
}
