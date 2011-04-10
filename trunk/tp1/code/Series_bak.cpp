#include <cmath>
#include <iostream>
//#include <string>
#include <cstdlib>
#include <cstdio>
#include <limits>

//#define big_mathLib float
#define big_mathLib double
//#define big_mathLib long double
#define int_mathLib unsigned long long

#include "Real.h"

using namespace std;

#define bestInt int

int_mathLib fact(int_mathLib x){
	if(x > 0){
		int_mathLib i = x-1;
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
	int_mathLib num;
	int_mathLib den;
	for(int i=0;i<cantIteraciones;i++){
		//cout << "i " << i << endl;
		
		num = fact(4*i)*(1103+26390*i);
		//cout << "num " << num << endl;
		
		double num_double = (double) num;
		//cout << "num_double " << num_double << endl;
	
		den = pow(fact(i),4) * pow(396,4*i);
		//cout << "den " << den << endl;
		
		double den_double = (double) den;
		//cout << "den_double " << den_double << endl;
		
		pi += num_double/den_double;
	}

	pi *= sqrt(8)/9801;
	
	return 1/pi;
}

int main(int argc, char** argv){
	//cout << "Maximum ull value: " << std::numeric_limits<unsigned long long>::max() << std::endl;
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
	cout.precision(10);
	for(int j=1;j<=cantIteraciones;j++)
		cout << "PI calculado con Ramanujan: " << Ramanujan(j) << endl;
	
	return 0;
}
