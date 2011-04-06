#include "Real.h"

/*
	No debemos controlar Nan ni Over/UnderFlow ya que las operaciones se realizan con doubles
	y eso se maneja automaticamente
*/


/*
	CHE NO ME GUSTA ESTO DSP ARREGLAR 
	this->convert(!isMask);
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
	_tdigits = 52-t_digits;
	_original = number;

	setMascara();

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
	bool isMask = true;
	double thisValue = this->convert(!isMask);
	double aValue	 = a.convert(!isMask);
	
	double resSum = thisValue + aValue;
	
	const Real* selector;
	if(this->_tdigits < a._tdigits)
		selector = &a;
	else 
		selector = this;
		
	Real resultSum(selector->_tdigits,selector->_truncates);
	resultSum.copyDoubleToArray(resultSum.filterPrecision(resSum));
	
	return resultSum;
}

Real Real :: operator* (const Real &a) const{
	bool isMask = true;
	double thisValue = this->convert(!isMask);
	double aValue    = a.convert(!isMask);
	
	double resMult	 = thisValue * aValue;

	const Real* selector;
	if(this->_tdigits < a._tdigits)
		selector = &a;
	else 
		selector = this;
	
	Real resultMult(selector->_tdigits, selector->_truncates);
	resultMult.copyDoubleToArray(filterPrecision(resMult));
	
	return resultMult;
}


Real Real :: operator- (const Real &a) const{
	bool isMask = true;
	double thisValue = this->convert(!isMask);
	double aValue	 = a.convert(!isMask);
	
	double resSub	 = thisValue - aValue;

	const Real* selector;
	if(this->_tdigits < a._tdigits)
		selector = &a;
	else 
		selector = this;

	Real resultSub(selector->_tdigits, selector->_truncates);
	resultSub.copyDoubleToArray(filterPrecision(resSub));
	
	return resultSub;
}

Real Real :: operator/ (const Real &a) const{
	bool isMask = true;
	double thisValue = this->convert(!isMask);
	double aValue 	 = a.convert(!isMask);
	
	double resDiv	 = thisValue / aValue;

	const Real* selector;
	if(this->_tdigits < a._tdigits)
		selector = &a;
	else 
		selector = this;

	Real resultDiv(selector->_tdigits, selector->_truncates);

	resultDiv.copyDoubleToArray(filterPrecision(resDiv));

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
	bool isMask = true;
	double real = this->convert(!isMask);

	real = sqrt(real);
	
	this->copyDoubleToArray(real);
	
	return *this;
}
	
	
double Real :: convert(bool isMask) const{
	double realConverted;
	if(isMask){
		realConverted = *(double*) _mascaraTdigits;
	}
	else 
	{
		realConverted = *(double*) _real;
	}
	
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
	
	mantissa &= getMascara();
	
	return mantissa;
}

ullInt Real :: getMascara() const{
	ullInt mask = *(ullInt*) &_mascaraTdigits;
	return mask>>1;
}


double Real :: filterPrecision(double value) const{
	ullInt filteredDouble;
	ullInt mask;
	
	bool isMask = true;
	mask = doubleToInt(this->convert(isMask));	

	if(!_truncates)
		value += doubleToInt(getRoundFactor(this->_tdigits));
		
	filteredDouble = doubleToInt(value) & mask;	
	return intToDouble(filteredDouble);
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
//	cout << "original" << endl;
//	printInt(getMascara());
	
	llInt mascara = *(llInt*) &_mascaraTdigits;
	
	int shiftDer = 52-_tdigits;
	int shiftIzq = _tdigits;
	
	mascara = mascara >> shiftDer;
//	cout << "shift der t bits = " << shiftDer << endl;
///	printInt((ullInt) mascara);

	mascara = mascara << shiftIzq;
//	cout << "shift izq t bits = " << shiftIzq << endl;
//	printInt((ullInt) mascara);
		
	char* pmask = (char*) &mascara;
	for(int i=0;i<sizeof(double);i++){
		_mascaraTdigits[i] = pmask[i];
	}
//	cout << "in mem" << endl;
//	printInt(getMascara());
}

void Real :: printReal(){
    char * desmond = (char *) & _real;
    int i;
	cout << "int representation (of array of class)   --> " << _original << ".0" << endl;
	cout << "double representation (of array of class)--> " << convert(false) << endl;
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
  stream << real.convert(false);
  return stream; 
}


