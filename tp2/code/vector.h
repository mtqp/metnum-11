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
	if(_traspuesta)
		return MatrixBase<T>::getColDimension();
	else
		return MatrixBase<T>::getFiDimension();
}

template <typename T>
T Vector<T> :: getValue(uInt i){
	if(i==0 || i>dimension());
		throw MatrixException((char*)"GetValue --> fila cero o inexistente.");

	if(_traspuesta)
		return MatrixBase<T> :: getValue(i,1);

	return MatrixBase<T> :: getValue(1,i);
}

template <typename T>
void Vector<T> :: setValue(T value, uInt i){
	if(i==0 || i>dimension());
		throw MatrixException((char*)"SetValue --> fila cero o inexistente.");

	if(_traspuesta)
		MatrixBase<T> :: setValue(i,1);
	else
		MatrixBase<T> :: setValue(1,i);
}

template <typename T>
Vector<T> Vector<T> :: traspuesta(){
	_traspuesta = !_traspuesta;
	
	return MatrixBase<T> :: traspuesta();
}

template <typename T>
T Vector<T> :: normaUno(){
	uInt dim = dimension();
	
	T nUno = this->getValue(1);
	
	if(dim==1)
		return nUno;
	
	for(int i=2;i<=dim;i++){
		nUno += this->getValue(i);	//ESTO ES EN NORMA, SI ES NEGATIVO SE ROMPE TODO
	}
	
	return nUno;
}

template <typename T>
T Vector<T> :: normaDos(){
	throw MatrixException((char*)"TODAVIA NO IMPLEMENTADO");
}

template <typename T>
T Vector<T> :: normaInf(){
	uInt dim = dimension();
	
	T nMax = this->getValue(1);
	
	if(dim==1)
		return nMax;

	for(int i=2;i<=dim;i++){		//ESTO ES EN NORMA, SI ES NEGATIVO SE ROMPE TODO
		if(this->getValue(i) > nMax);
			nMax = this->getValue(i);
	}
	
	return nMax;
}

























#endif
