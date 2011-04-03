#include "Real.h"

/*
	No debemos controlar Nan ni Over/UnderFlow ya que las operaciones se realizan con doubles
	y eso se maneja automaticamente
*/

/*	AVERIGUAR POR FAVOR!:
	Porque el uso de los operadores funciona solo si el objeto se crea con el mismo
	constructor??!!!!?????
*/

Real ::	Real(){
	Real(0,52,true);
}

Real ::	Real(llInt valor){
	Real(valor,52,true);
}

Real ::	Real(int t_digits, bool truncates){
	Real(0,t_digits,truncates);
}

Real ::	Real(llInt number, int t_digits,bool truncates){
	_truncates = truncates;
	_tdigits = t_digits;
	_original = number;

	//setMascara();	//-->chequear que este bien.

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

Real Real :: operator+ (const Real &a) const{
/*
	COMO HACEMOS LA SUMA, PRECOND MISMO TRUNCAMIENTO Y TDIGITS O LO SOLUCIONAMOS AL MENOR!?!?!?
*/
	double thisValue = this->convert();
	double aValue	 = a.convert();
	
	double resSum = thisValue + aValue;
	
	//harcoded al this
	Real resultSum(this->_tdigits,this->_truncates);
	resultSum.copyDoubleToArray(resSum);
	
	return resultSum;
}

Real Real :: operator* (const Real &a) const{
/*
	Nuevamente no le estamos dando pelota al truncamiento y los tdigits
*/
	double thisValue = this->convert();
	double aValue    = a.convert();
	
	double resMult	 = thisValue * aValue;
	
	Real resultMult(this->_tdigits, this->_truncates);
	resultMult.copyDoubleToArray(resMult);
	
	return resultMult;
}


Real Real :: operator- (const Real &a) const{
/*
	Nuevamente no le estamos dando pelota al truncamiento y los tdigits
*/
	double thisValue = this->convert();
	double aValue	 = a.convert();
	
	double resSub	 = thisValue - aValue;

	Real resultSub(this->_tdigits, this->_truncates);
	resultSub.copyDoubleToArray(resSub);
	
	return resultSub;
}

Real Real :: operator/ (const Real &a) const{
/*
	Nuevamente no le estamos dando pelota al truncamiento y los tdigits
*/
	double thisValue = this->convert();
	double aValue 	 = a.convert();
	
	double resDiv	 = thisValue / aValue;

	Real resultDiv(this->_tdigits, this->_truncates);
	resultDiv.copyDoubleToArray(resDiv);
	
	return resultDiv;	
}

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

Real Real :: squareRoot(){
	double real = this->convert();

	real = sqrt(real);
	
	this->copyDoubleToArray(real);
	
	return *this;
}
	
	
double Real :: convert() const{
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
		mantissa = mantissa >> shift; //CHEQUEAR QUE ESTA RAMA FUNCIONE CORRECTAMENTE Q NO LA PROBE
	} 
	else
	{
		shift 	 = 52-shift+1;
		mantissa = mantissa << shift;	
	}
	
	//mantissa &= getMascara();
	
	return mantissa;
}

ullInt Real :: getMascara(){
	ullInt mask = *(ullInt*) &_mascaraTdigits;
	return mask;
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

void Real :: setMascara(){
	memset((void*) &_mascaraTdigits,255,8);
	
	ullInt mascara = (ullInt) _mascaraTdigits;
	
	mascara = mascara >> 52-_tdigits;
	mascara = mascara << _tdigits;
	
	char* pmask = (char*) &mascara;
	for(int i=0;i<sizeof(double);i++){
		_mascaraTdigits[i] = pmask[i];
	}
}

void Real :: printReal(){
    char * desmond = (char *) & _real;
    int i;
	cout << "int representation (of array of class)   --> " << _original << ".0" << endl;
	cout << "double representation (of array of class)--> " << convert() << endl;
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

//fijarse si no se necesita ver cierta precisión del numero o demás
//pensar que se esta convirtiendo a double y se imprime, fijarse si se quiere
//realizar la conversion a manopla!
ostream &operator<<(ostream &stream, Real real)
{
  stream << real.convert();
  return stream; 
}


