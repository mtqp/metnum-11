#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "includes.h"
#include "matrix_exceptions.h"
#include "matrix_base.h"

template <class T>
class Vector : public MatrixBase<T>{
	public:
		Vector(uInt dim);
		//Vector(const Vector<T>& v);
		Vector(uInt dim, bool traspuesta);
		~Vector();
	
		uInt dimension() const;
	
		T getValue(uInt i) const;
		void setValue(T value, uInt i);
	
		Vector<T> traspuesta() const;
	
		T normUno() const;	//no devuelve doubles o algo asi?
		T normDos() const;
		T normInf() const;
		
		/*para hacer anda la herencia*/
		Vector<T>& operator= (const MatrixBase<T> &mb);
		
	private:
		bool _traspuesta;
};

template <typename T>
Vector<T> :: Vector(uInt dim) : MatrixBase<T>(1,dim){
	_traspuesta = false;
}

/*
template <typename T>
Vector<T> :: Vector(const Vector<T>& v){
	this->_traspuesta = v._traspuesta;
	
	uInt pres = v.dimension();
	
	for(int i=1;i<=pres;i++)
		this->setValue(v.getValue(i),i);
}*/

template <typename T>
Vector<T> :: Vector(uInt dim, bool traspuesta) : MatrixBase<T>(1,dim){
	_traspuesta = traspuesta;
	
	if(_traspuesta)
		MatrixBase<T> :: traspuesta();
}

template <typename T>
Vector<T> :: ~Vector(){
}

template <typename T>
uInt Vector<T> :: dimension() const {
	if(!_traspuesta)
		return MatrixBase<T>::getColDimension();
	else
		return MatrixBase<T>::getFiDimension();
}

template <typename T>
T Vector<T> :: getValue(uInt i) const {
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
Vector<T> Vector<T> :: traspuesta() const {
	MatrixBase<T> mb(MatrixBase<T> :: traspuesta());
	Vector<T>* vt = static_cast<Vector<T>*>(&mb);

	return *vt;	
}

template <typename T>
Vector<T>& Vector<T> :: operator= (const MatrixBase<T> &mb){
	uInt dimFi = mb.getFiDimension();
	uInt dimCol= mb.getColDimension();
	uInt vDim = this->dimension();
	
	bool validDer = (dimFi==1 && dimCol>1 && dimCol==vDim);
	bool validTrasp=(dimCol==1 && dimFi>1 && dimFi==vDim);
	
	if(!validDer && !validTrasp)
		throw MatrixException((char*)"Asignacion entre vectores y matrices invalida");

	this->_traspuesta = validTrasp;

	if(this->_traspuesta){
		for(int i=1;i<=vDim;i++)
			this->setValue(mb.getValue(i,1),i);		
	}
	else {
		for(int i=1;i<=vDim;i++)
			this->setValue(mb.getValue(1,i),i);
	}

	return *this;
}

template <typename T>
T Vector<T> :: normUno() const {
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
T Vector<T> :: normDos() const {
	uInt dim = dimension();
	
	T nDos = this->getValue(1);
	
	if(dim==1)
		return sqrt(nDos*nDos);
	
	for(int i=2;i<=dim;i++){
		nDos += this->getValue(i)*this->getValue(i);
	}
	
	return sqrt(nDos);	
}

template <typename T>
T Vector<T> :: normInf() const {
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
