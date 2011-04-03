#include "Real.h"

Real ::	Real(){
	Real(0,52,true);
}

Real ::	Real(llInt valor){
	Real(valor,52,true);
}

Real ::	Real(llInt number, int t_digits,bool truncates){
	_truncates = truncates;
	_tdigits = t_digits;
	_original = number;

	memset((void *) &_real, 0, 8);
	if(number==0){
		return;
	}

	ullInt sign;
	ullInt exp;
	ullInt mantissa;

	sign 	 = getSign();
	exp  	 = getExp();
	mantissa = getMantissa();
	
	copyDoubleToArray(sign,exp,mantissa);
}

Real ::	~Real(){
}

/*no olvidar que todas estas operaciones pueden dar Nan u OverFlow! pensar como controlar.*/


const Real Real :: operator+ (const Real &a) const{
/*
  // Add this instance's value to other, and return a new instance
  // with the result.
  const MyClass MyClass::operator+(const MyClass &other) const {
    MyClass result = *this;     // Make a copy of myself.  Same as MyClass result(*this);
    result += other;            // Use += to add other to the copy.
    return result;              // All done!
  }

*/

}

Real ::	Real operator* (Real a){}
Real ::	Real operator- (Real a){}
//Real ::	Real operator/ (Real a, Real b){}
Real& Real :: operator= (const Real &a){
	if(this!=&a){
		this->_truncates = a._truncates;
		this->_tdigits	 = a._tdigits;
		this->_original	 = a._original;
	
		for(int i=0;i<sizeof(double);i++){
			this->_real[i] = a._real[i];
		}
	}
	return *this;
}
//Real ::	Real operator= (ullInt a){}
Real ::	Real raizCuad(){}
	
	
double Real :: convert(){
	double realConverted = *(double*) _real;
	return realConverted;
}

ullInt Real :: getSign(){
	ullInt signedNumber = 0;
	
	if(_original<0)
	{
		signedNumber = signedNumber+1<<63;
	}
	
	return signedNumber;
}

ullInt Real :: getExp(){
	ullInt number = cleanSign(_original);
	ullInt exp 	  = 0;
	
	exp = (ullInt) placesToShift(number,0); /*se le pasa el cero, suponiendo notacion 0.xxxx * e^(+- algo)*/
	exp += 1023ull;							/*lo normaliza al desvio 1023*/
	exp -= 1ull;

	exp = exp << 52;
	
	return exp;
}

/*tener en cuenta que la creacion de la mantissa no esta chequeando si TRUNCA y los TDIGITS!!!*/
ullInt Real :: getMantissa(){
	ullInt mantissa;
	int shift;

	mantissa = cleanSign(_original);
	shift    = placesToShift(mantissa,0);

	mantissa = cleanFirstNotZero(mantissa,shift);

	if(shift>51){	//==>va a existir truncamiento del numero
		shift	 = 63 - shift;
		mantissa = mantissa >> shift; //chequear esta rama dsp
	} 
	else
	{
		shift 	 = 52-shift+1;
		mantissa = mantissa << shift;	
	}
	
	return mantissa;
}

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
	ullInt real = 0;

	real |= sign;
	real |= exp;
	real |= mantissa;

	char* r_array = (char*) &real;

	for(int i=0;i<sizeof(ullInt);i++){
		_real[i] = r_array[i];
	}
}

void Real :: copyDoubleToArray(double number){
	char* real = (char*) &number;
	
	for(int i=0;i<sizeof(double);i++){
		_real[i] = real[i];
	}
}

