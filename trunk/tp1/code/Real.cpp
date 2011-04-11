#include "Real.h"

/*
	No debemos controlar Nan ni Over/UnderFlow ya que las operaciones se realizan con doubles
	y eso se maneja automaticamente
*/

/*
	Public
*/

Real ::	Real(){
	setReal(0,52,true);
}

Real ::	Real(llInt valor){
	setReal(valor,52,true);
}

Real :: Real(double value, int t_digits, bool truncates){
/*	ullInt int_value = doubleToInt(value);
	
	_t_digits = t_digits;
	_truncates= truncates;
	_original = int_value;

	this.save(value);*/
}

Real ::	Real(int t_digits, bool truncates){
	setReal(0,t_digits,truncates);
}

Real ::	Real(llInt number, int t_digits,bool truncates){
	setReal(number,t_digits,truncates);
}

Real ::	~Real(){
}

int Real :: presicion() const{
	return _tdigits;
}

bool Real :: truncate() const{
	return _truncates;
}

Real Real :: operator+ (const Real &a){
	double thisValue = this->convert();
	double aValue	 = a.convert();
	
	double resSum = thisValue + aValue;
	
	const Real* selector;
	if(this->_tdigits < a._tdigits)
		selector = &a;
	else 
		selector = this;
		
	Real resultSum(selector->_tdigits,selector->_truncates);
	
	resultSum.save(resSum);
	
	return resultSum;
}

Real Real :: operator* (const Real &a){
	double thisValue = this->convert();
	double aValue    = a.convert();
	
	double resMult	 = thisValue * aValue;

	const Real* selector;
	if(this->_tdigits < a._tdigits)
		selector = &a;
	else 
		selector = this;
	
	Real resultMult(selector->_tdigits, selector->_truncates);

	resultMult.save(resMult);
	
	return resultMult;
}


Real Real :: operator- (const Real &a){
	double thisValue = this->convert();
	double aValue	 = a.convert();
	
	double resSub	 = thisValue - aValue;

	const Real* selector;
	if(this->_tdigits < a._tdigits)
		selector = &a;
	else 
		selector = this;

	Real resultSub(selector->_tdigits, selector->_truncates);

	resultSub.save(resSub);

	return resultSub;
}

Real Real :: operator/ (const Real &a){
	double thisValue = this->convert();
	double aValue 	 = a.convert();
	
	double resDiv	 = thisValue / aValue;

	const Real* selector;
	if(this->_tdigits < a._tdigits)
		selector = &a;
	else 
		selector = this;

	Real resultDiv((selector->_tdigits), selector->_truncates);

	resultDiv.save(resDiv);

	return resultDiv;	
}

Real& Real :: operator= (const Real &a){
	if(this!=&a){
		this->_truncates = a._truncates;
		this->_tdigits	 = a._tdigits;
		this->_original	 = a._original;
	
		for(int i=0;i<sizeof(double);i++){
			this->_real[i] = a._real[i];
			this->_mascaraTdigits[i] = a._mascaraTdigits[i];
		}
	}
	return *this;
}

double Real :: convert() const{
	double realConverted;
	realConverted = *(double*) _real;
	return realConverted;
}

void Real :: save(double value){
	copyDoubleToArray(value);
	filterPrecision();
}

void Real :: printReal(){
    char * desmond = (char *) & _real;
    int i;
    cout.precision(_tdigits);
	cout << "int representation (of array of class)   --> " << _original << ".0" << endl;
	cout << "double representation (of array of class)--> " << convert() << endl;
	printNotacion();
	
	unsigned char* bits = (unsigned char*) malloc(sizeof(unsigned char)*8);

    for (i=sizeof(double)-1; i>=0; i--) {
        printCharsetInBits(desmond[i], bits);
        printf ("%s ", bits);
    }
    printf ("\n");
    
    free(bits);
}

void Real :: printRealBits(){
char * desmond = (char *) & _real;
    int i;
   	unsigned char* bits = (unsigned char*) malloc(sizeof(unsigned char)*8);

    for (i=sizeof(double)-1; i>=0; i--) {
        printCharsetInBits(desmond[i], bits);
        printf ("%s ", bits);
    }
    printf ("\n");
    
    free(bits);
}

ostream &operator<<(ostream &stream, Real real){
  stream << real.convert();
  return stream; 
}

/*
	Private
*/

ullInt Real :: getMascara() const{
	ullInt mask = *(ullInt*) &_mascaraTdigits;
	return mask>>1;
}

int Real :: getExp(){
	unsigned char exp[4];
	
	memset((void*) &exp,0,4);
	
	unsigned char exp_0 = _real[6];
	unsigned char exp_1 = _real[7]; 

	exp_1 = exp_1 << 1;		//limpia signo
	exp_1 = exp_1 >> 1;
	
	exp_0 = exp_0 >> 4;		//limpia digitos provenientes de mantissa
	exp_0 = exp_0 << 4; 

	exp[0] = exp_0;
	exp[1] = exp_1;
	
	int intExp = *(int*) &exp;
	
	intExp = intExp >> 4;			//corre el valor a la parte menos significativa

	return intExp-1023;
}

void Real :: filterPrecision(){
	double value = convert();

	ullInt filteredDouble;
	ullInt mask;
	
	mask = getMascara();	

	int exp = getExp();

	if((!_truncates) && (_tdigits!=51)){
//		double redondeo = pot(base2,exp).convert();
		double redondeo = doublePot(2.0,exp);
		for(int i=0;i<_tdigits+5;i++){
			redondeo /= 2.0;
		}
		
		value += redondeo;
	}

	filteredDouble = doubleToInt(value) & mask;

	copyDoubleToArray(intToDouble(filteredDouble));
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
	
	_original = real;
}

void Real :: copyDoubleToArray(double number){
	char* real = (char*) &number;
	
	for(int i=0;i<sizeof(double);i++){
		_real[i] = real[i];
	}
	
	_original = doubleToInt(number);
}

void Real :: setMascara(){
	memset((void*) &_mascaraTdigits,255,8);
	
	llInt mascara = *(llInt*) &_mascaraTdigits;

	int shiftDer = _tdigits;
	int shiftIzq = 52-_tdigits;
	
	mascara = mascara >> shiftDer;
	mascara = mascara << shiftIzq;
		
	char* pmask = (char*) &mascara;
	for(int i=0;i<sizeof(double);i++){
		_mascaraTdigits[i] = pmask[i];
	}
}

void Real :: setReal(llInt number, int t_digits,bool truncates){
	_truncates = truncates;
	_tdigits = t_digits;
	_original = number;

	setMascara();

	memset((void *) &_real, 0, 8);
	if(number==0){
		return;
	}

	ullInt sign;
	ullInt exp;
	ullInt mantissa;

	sign 	 = getInitSign();
	exp  	 = getInitExp();
	mantissa = getInitMantissa();
	
	copyDoubleToArray(sign,exp,mantissa);
}

ullInt Real :: getInitSign(){
	ullInt signedNumber = 0;
	
	if(_original<0)
	{
		signedNumber = signedNumber+1<<63;
	}
	
	return signedNumber;
}

ullInt Real :: getInitExp(){
	ullInt number = cleanSign(_original);
	ullInt exp 	  = 0;
	
	exp = (ullInt) placesToShift(number,0); /*se le pasa el cero, suponiendo notacion 0.xxxx * e^(+- algo)*/
	exp += 1022ull;							/*lo normaliza al desvio 1023*/

	exp = exp << 52;
	
	return exp;
}

ullInt Real :: getInitMantissa(){
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

