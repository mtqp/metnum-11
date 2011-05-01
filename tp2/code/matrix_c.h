#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "includes.h"
#include "matrix_exceptions.h"

enum MatrixType{
	ID,
	TSup,
	TInf,
	Nula,
	Diag,
	Rand,
	BadK	
};

/*
	NOTA: 
		- Utilizar try catch para manejar casos bordes
		- Si se acude a metodos auxiliares, mientras no este implementado tirar excepcion de no implementado
	
*/

template <class T>
class Matrix : public MatrixBase<T>{
	public:
		Matrix(uInt dimFi, uInt dimCol);
		Matrix(T** data, uInt dimFi, uInt dimCol);
		Matrix(uInt dimFi, uInt dimCol, MatrixType type);
		~Matrix();
		
		Matrix<T> gaussianElim();
		Matrix<T> LU(); //o QR no sabemos
		Matrix<T> inverse();
		//T det();
		
		bool isTriang(bool superior);
		bool isId();
		
		T K();	//numero de condicion
	
		uInt maxUnderDiag(uInt j); 					//estrategia de pivoteo parcial
	private:
		void putZero(uInt i, uInt j, uInt pivot);	//pone el cero en esa posicion
		bool zeroDiag(uInt i);						//si la posicion ii tiene un cero
	
		T  	 normF();	
};

template <typename T>
Matrix<T> :: Matrix(uInt dimFi, uInt dimCol) : MatrixBase<T>(dimFi,dimCol){}

template <typename T>
Matrix<T> :: Matrix(T** data, uInt dimFi, uInt dimCol) : MatrixBase<T>(data,dimFi,dimCol) {} 

template <typename T>
Matrix<T> :: Matrix(uInt dimFi, uInt dimCol, MatrixType type) : MatrixBase<T>(dimFi, dimCol){
	throw MatrixException((char*)"Generador NO implementado");
}

template <typename T>
Matrix<T> :: ~Matrix(){}

template <typename T>
bool Matrix<T> :: isTriang(bool superior){
	bool res = true;
	uInt dimFi = MatrixBase<T> :: getFiDimension();
	
	if(superior){
		for(int i=2; i<=dimFi; i++)
			for(int j=1; j<i; j++)
				res &= this->getValue(i,j)==0;
	}
	else{
		uInt dimCol = MatrixBase<T> :: getColDimension(); 
		for(int i=1; i<dimFi; i++)
			for(int j=i+1; j<=dimCol; j++)
				res &= this->getValue(i,j)==0;
	}
	
	return res;
}

template <typename T>
bool Matrix<T> :: isId(){
	bool res = true;
	uInt dimFi = MatrixBase<T> :: getFiDimension();
	uInt dimCol = MatrixBase<T> :: getColDimension();
	
	for(int i=1; i<=dimFi; i++)
		for(int j=1; j<=dimCol; j++)
			res &= (i==j && this->getValue(i,j)==1) || (i!=j && this->getValue(i,j)==0);
			
	return res;
}

template <typename T>
uInt Matrix<T> :: maxUnderDiag(uInt j){
	uInt dimFi = MatrixBase<T> :: getFiDimension();
	
	T pivot = this->getValue(j,j);
	uInt pivot_pos = j;
	
	for(int i=j+1; i<=dimFi; i++){
		T elem = this->getValue(i,j);
		if(elem>pivot){
			pivot = elem;
			pivot_pos=i;
		}
	}

	return pivot_pos;
}

template <typename T>
T Matrix<T> :: normF(){
	uInt dimFi = MatrixBase<T> :: getFiDimension();
	uInt dimCol = MatrixBase<T> :: getColDimension();
	
	T normF = this->getValue(1,1);
	
	if(dimFi==1 && dimCol==1) return normF;

	for(int i=1; i<=dimFi; i++)
		for(int j=1; j<=dimCol; j++)
			normF += this->getValue(i,j)*this->getValue(i,j);
	
	normF -= this->getValue(1,1);
	return squareRoot(normF);
}

#endif
