#include "Real.h"

Real ::	Real(){
	Real(0,52,true);
}

Real ::	Real(llInt valor){ 	//se va o no se va???
	Real(valor,52,true);
}


/*For double precision, the exponent field is 11 bits, and has a bias of 1023.
  nos falta agregar eso
*/

/*
	Que debe hacer:
		- conseguir el signo
		- saber en QUE posicion esta el bit mas significativo en uno (ese no se cuenta para pegar en el ad)
		- cargar el exponente con el desvio de 1023, es decir... 0000 = -1023
*/

Real ::	Real(llInt number, int t_digits,bool truncates){
	_truncates = truncates;
	_tdigits = t_digits;
	_original = number;

	ullInt sign;
	ullInt exp;
	ullInt mantissa;

	sign 	 = getSign();
	exp  	 = getExp();
	mantissa = getMantissa();
	
	printInt(sign);
	
	copyDoubleToArray(sign,exp,mantissa);
	
}

Real ::	~Real(){
}

ullInt Real :: getSign(){
	ullInt signedNumber = 0;
	
	if(_original<0)
	{
		signedNumber = signedNumber+1<<63;
	}
	
	return signedNumber;
}

ullInt Real :: getExp(){}
ullInt Real :: getMantissa(){}


/*no olvidar que todas estas operaciones pueden dar Nan u OverFlow! pensar como controlar.*/

Real ::	Real operator+ (Real a){} //--> van a ser constantes o no? PENSAR
Real ::	Real operator* (Real a){}
Real ::	Real operator- (Real a){}
//Real ::	Real operator/ (Real a, Real b){}
//Real ::	Real operator= (Real a){}
//Real ::	Real operator= (ullInt a){}
Real ::	Real raizCuad(){}
	
	
double Real :: convert(){}

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

void Real :: copyDoubleToArray(ullInt sign, ullInt exp, ullInt mantissa){
	/*implementar*/
}


/*Real ::	Real(llInt numero, int t_digitos,bool trunca){
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

	int shift_mantisa = 52-exponente+1;
	//shift_mantisa = 52; //todavia no entiendo xq, ahora hardcore:

	cout << shift_mantisa << " mantisa shifter" << endl;

	/*cout << "######################################################" << endl;
	printInt(exponente);	
	cout << "######################################################" << endl;
	cout << "exponent  " << exponente << endl;
	
	
	exponente = exponente<<51;				//posicionandose para armar el real!
	/*cout << "exponent shifteed  " << exponente << endl;
	cout << "######################################################" << endl;
	printInt(exponente);	
	cout << "######################################################" << endl;		
	
	///*esto esta mal!!!
//	if(signo){				//busca signo
	//	exponente *= -1;
//	}
	///////////////////

	ullInt signo_exponente;
	signo_exponente = exponente; //tenemos los 1ros doce bits armados en exponente!

	if(shift_mantisa<0){
		valor = valor >> ((-1)*shift_mantisa);
	}
	else {
		cout << "######################################################" << endl;
		printInt(valor);	
		cout << "######################################################" << endl;		
		valor = valor << shift_mantisa;
		cout << "######################################################" << endl;
		printInt(valor);	
		cout << "######################################################" << endl;		
	}

	cout << "######################################################" << endl;
	printInt(signo_exponente);	
	cout << "######################################################" << endl;		
	signo_exponente |= valor;
	cout << "######################################################" << endl;
	printInt(signo_exponente);	
	cout << "######################################################" << endl;
	copyDoubleToArray(signo_exponente);	//dsp si se hace sobrecarga del = esta linea puede volar
}
*/


