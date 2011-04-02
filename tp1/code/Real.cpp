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

Real ::	Real() : this(0,52,true){
}

Real ::	Real(bestInt valor) : this(valor,52,true){
}//se va o no se va???

Real ::	Real(bestInt numero, char t_digitos,bool trunca){
	_trunca = trunca;
	_tdigitos = t_digitos;

	long long  	valor = (long long) numero; 
	bool 		signo = numero<0;

	memset((void *) &real, 0, 8);
	if(valor == 0){
		return;
	}

	if(signo){
		valor *= -1;
	}
	
	ullInt valor_exp = (ullInt) valor;
	long long exponente = 0;	//la posicion del 1 MAS significativo (exceptuando el signo)	
	
	while(valor_exp != 0){		//busca cual es el exponente al que hay q elevar
		valor_exp>>1;
		exponente++;
	}	

	int shift_mantisa = 52-exponente;

	exponente<<51;				//posicionandose para armar el real!
	
	/*esto esta mal!!!*/
	if(signo){				//busca signo
		exponente *= -1;
	}
	///////////////////

	ullInt signo_exponente;
	signo_exponente = exponente //tenemos los 1ros doce bits armados en exponente!

	if(shift_mantisa<0){
		valor >> ((-1)*shift_mantisa)
	}
	else {
		valor << shift_mantisa;
	}
	
	signo_exponente |= valor;
	
	_real = signo_exponente;

}

Real ::	~Real(){
}

/*no olvidar que todas estas operaciones pueden dar Nan u OverFlow! pensar como controlar.*/

Real ::	Real operator+ (Real a){} //--> van a ser constantes o no? PENSAR
Real ::	Real operator* (Real a){}
Real ::	Real operator- (Real a){}
Real ::	Real operator/ (Real a){}
Real ::	Real operator= (const Real a){}
Real ::	Real operator= (const bestInt a){}
Real ::	Real raizCuad(){}
	
	
double convertir(){}


/*por dios que horrible!*/
void mostrar(double *x)
{
    unsigned char c0 = *((char*)x + 7);
    unsigned char c1 = *((char*)x + 6);
    unsigned char c2 = *((char*)x + 5);
    unsigned char c3 = *((char*)x + 4);
    unsigned char c4 = *((char*)x + 3);
    unsigned char c5 = *((char*)x + 2);
    unsigned char c6 = *((char*)x + 1);
    unsigned char c7 = *((char*)x);

    char todo[65];

    unsigned char pot = 128;
    for(int i=0; i<8; ++i)
    {
        todo[i] = '0' + (c0 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=8; i<16; ++i)
    {
        todo[i] = '0' + (c1 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=16; i<24; ++i)
    {
        todo[i] = '0' + (c2 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=24; i<32; ++i)
    {
        todo[i] = '0' + (c3 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=32; i<40; ++i)
    {
        todo[i] = '0' + (c4 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=40; i<48; ++i)
    {
        todo[i] = '0' + (c5 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=48; i<56; ++i)
    {
        todo[i] = '0' + (c6 / pot) % 2;
        pot /= 2;
    }

    pot = 128;
    for(int i=56; i<64; ++i)
    {
        todo[i] = '0' + (c7 / pot) % 2;
        pot /= 2;
    }

    todo[64] = 0;

    char signo = todo[0];
    char exponente[11];
    char mantisa[52];

    int _exponente = 0;
    float _mantisa = 1.0;

    for(int i=0, pot=128; i<11; ++i)
    {
        exponente[i] = todo[i+1];
        _exponente += (exponente[i] - '0') * pot;
        pot /= 2;
    }

    float _pot = 0.5;
    for(int i=0; i<52; ++i)
    {
        mantisa[i] = todo[i+11];
        _mantisa += (mantisa[i] - '0') * _pot;
        _pot /= 2;
    }

    exponente[11] = 0;
    mantisa[52] = 0;

    printf( "signo = %c, ", signo );
    printf( "exp = %s (%d), ", exponente, _exponente );
    printf( "mant = 1.%s \n", mantisa );
//  printf( "%3.5f = %s \n", *x, todo );
}



