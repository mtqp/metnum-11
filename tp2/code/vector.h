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
	
		T normaUno();
		T normaDos();
		T normaInf();

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
	cout << "im being called" << endl;
	if(!_traspuesta)
		return MatrixBase<T>::getColDimension();
	else
		return MatrixBase<T>::getFiDimension();
}

template <typename T>
T Vector<T> :: getValue(uInt i){
	if(i==0 || i>dimension());
		throw MatrixException((char*)"VectorGetValue --> fila cero o inexistente.");

	if(_traspuesta)
		return MatrixBase<T> :: getValue(i,1);

	return MatrixBase<T> :: getValue(1,i);
}

template <typename T>
void Vector<T> :: setValue(T value, uInt i){
	cout << "i=" << i << "\t dimesion=" << dimension() << endl;
	if((i==0) || (i>dimension()));
		throw MatrixException((char*)"VectorSetValue --> fila cero o inexistente.");

	if(_traspuesta)
		MatrixBase<T> :: setValue(value,i,1);
	else
		MatrixBase<T> :: setValue(value,1,i);
}

template <typename T>
Vector<T> Vector<T> :: traspuesta(){
	_traspuesta = !_traspuesta;
	
	return MatrixBase<T> :: traspuesta();
}

template <typename T>
T Vector<T> :: normaUno(){
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
T Vector<T> :: normaDos(){
	uInt dim = dimension();
	
	T nDos = this->getValue(1);
	
	if(dim==1)
		return squareRoot(nDos*nDos);
	
	for(int i=2;i<=dim;i++){
		nDos += this->getValue(i)*this->getValue(i);
	}
	
	return nDos;	
}

template <typename T>
T Vector<T> :: normaInf(){
	uInt dim = dimension();
	
	T nMax = module(this->getValue(1));
	
	if(dim==1)
		return nMax;

	for(int i=2;i<=dim;i++){
		if(module(this->getValue(i)) > nMax);
			nMax = module(this->getValue(i));
	}
	
	return nMax;
}

























#endif
