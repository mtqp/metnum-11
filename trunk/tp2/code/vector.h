#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "includes.h"
#include "matrix_exceptions.h"

//#define MatrixBase<T> base.

template <class T>
class Vector : public MatrixBase<T>{
	public:
		Vector(uInt dim);
		Vector(uInt dim, bool traspuesta);
		~Vector();
	
		uInt dimension();
	
		T getValue(uInt i);
		void setValue(T value, uInt i);
	
		Vector<T> traspuesta();
	
		T normUno();
		T normDos();
		T normInf();

	private:
		bool _traspuesta;
};

template <typename T>
Vector<T> :: Vector(uInt dim) : MatrixBase<T>(1,dim){
	_traspuesta = false;
}

template <typename T>
Vector<T> :: Vector(uInt dim, bool traspuesta) : MatrixBase<T>(1,dim){
	_traspuesta = traspuesta;
	
	if(_traspuesta)
		MatrixBase<T> :: traspuesta();
}

template <typename T>
Vector<T> :: ~Vector(){}

template <typename T>
uInt Vector<T> :: dimension(){
	if(!_traspuesta)
		return MatrixBase<T>::getColDimension();
	else
		return MatrixBase<T>::getFiDimension();
}

template <typename T>
T Vector<T> :: getValue(uInt i){
	if(i==0 || i>dimension())
		throw MatrixException((char*)"VectorGetValue --> fila cero o inexistente.");

	if(_traspuesta)
		return MatrixBase<T> :: getValue(i,1);

	return MatrixBase<T> :: getValue(1,i);
}

template <typename T>
void Vector<T> :: setValue(T value, uInt i){
	if((i==0) || (i>dimension()))
		throw MatrixException((char*)"VectorSetValue --> fila cero o inexistente.");

	if(_traspuesta)
		MatrixBase<T> :: setValue(value,i,1);
	else
		MatrixBase<T> :: setValue(value,1,i);
}

template <typename T>
Vector<T> Vector<T> :: traspuesta(){
//	_traspuesta = !_traspuesta;
	MatrixBase<T> mb = MatrixBase<T> :: traspuesta();

	Vector<T>* vt = static_cast<Vector<T>*>(&mb);
	// ­Heredada* h = static_cast<Heredada*>(&base);

	vt->_traspuesta = !_traspuesta;

	return *vt;
}

template <typename T>
T Vector<T> :: normUno(){
	uInt dim = dimension();
	
	T nUno = module(this->getValue(1));
	
	if(dim==1)
		return nUno;
	
	for(int i=2;i<=dim;i++){
		nUno += module(this->getValue(i));
	}
	
	return nUno;
}

template <typename T>
T Vector<T> :: normDos(){
	uInt dim = dimension();
	
	T nDos = this->getValue(1);
	
	if(dim==1)
		return squareRoot(nDos*nDos);
	
	for(int i=2;i<=dim;i++){
		nDos += this->getValue(i)*this->getValue(i);
	}
	
	return squareRoot(nDos);	
}

template <typename T>
T Vector<T> :: normInf(){
	uInt dim = dimension();
	
	T nMax = module(this->getValue(1));
	
	if(dim==1)
		return nMax;

	for(int i=2;i<=dim;i++){
		if(module(this->getValue(i)) > nMax)
			nMax = module(this->getValue(i));
	}
	
	return nMax;
}

























#endif
