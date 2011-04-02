#include "Real.h"

/*
double convertir();
bool _trunca;
char* _real;
*/

/*

	cout << sizeof(unsigned long long) << endl; --> 8
	cout << sizeof(unsigned long) << endl;		--> 4
	cout << sizeof(int) << endl;				--> 4
	cout << sizeof(double) << endl;				--> 8
*/

#define ullInt unsigned long long

/*Real ::	Real(){
	Real(0,52,true);
}

Real ::	Real(bestInt valor){
	Real(valor,52,true);
}//se va o no se va???
*/
Real ::	Real(bestInt numero, int t_digitos,bool trunca){
	_trunca = trunca;
	_tdigitos = t_digitos;

	_original = numero;

	long long  	valor = (long long) numero; 
	bool 		signo = numero<0;

	memset((void *) &_real, 0, 8);
	if(valor == 0){
		return;
	}

	if(signo){
		valor *= -1;
	}
	
	ullInt valor_exp = (ullInt) valor;
	long long exponente = 0;	//la posicion del 1 MAS significativo (exceptuando el signo)	
	
	while(valor_exp != 0){		//busca cual es el exponente al que hay q elevar
		valor_exp = valor_exp>>1;
		exponente++;
		cout<< valor_exp << endl;
	}	

	int shift_mantisa = 52-exponente;

	exponente = exponente<<51;				//posicionandose para armar el real!
	
	/*esto esta mal!!!*/
/*	if(signo){				//busca signo
		exponente *= -1;
	}*/
	///////////////////

	ullInt signo_exponente;
	signo_exponente = exponente; //tenemos los 1ros doce bits armados en exponente!

	if(shift_mantisa<0){
		valor = valor >> ((-1)*shift_mantisa);
	}
	else {
		valor = valor << shift_mantisa;
	}
	
	signo_exponente |= valor;
	
	copyDoubleToArray(signo_exponente);	//dsp si se hace sobrecarga del = esta linea puede volar
}

Real ::	~Real(){
}

/*no olvidar que todas estas operaciones pueden dar Nan u OverFlow! pensar como controlar.*/

Real ::	Real operator+ (Real a){} //--> van a ser constantes o no? PENSAR
Real ::	Real operator* (Real a){}
Real ::	Real operator- (Real a){}
//Real ::	Real operator/ (Real a, Real b){}
//Real ::	Real operator= (Real a){}
//Real ::	Real operator= (bestInt a){}
Real ::	Real raizCuad(){}
	
	
double Real :: convertir(){}

void Real :: printReal(){
    char * desmond = (char *) & _real;
    int i;
	cout << "real representation --> " << _original << ".0" << endl;;
	printNotacion();
	
	unsigned char* bits = (unsigned char*) malloc(sizeof(unsigned char)*8);

    for (i=sizeof(double)-1; i>=0; i--) {
        //printf ("%02X ", desmond[i]);		si se quiere en Hex
        printCharsetInBits(desmond[i], bits);
        printf ("%s ", bits);
    }
    printf ("\n");
    
    free(bits);
}

void Real :: copyDoubleToArray(double value){
	char* ad = (char*) &value;

	for(int i=0;i<8;i++){
		_real[i] = ad[i];
	}
}

