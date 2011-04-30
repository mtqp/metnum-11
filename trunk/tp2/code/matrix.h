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
		T det();
		
		bool isTriang(bool superior);
		bool isId();
		
		T K();	//numero de condicion
		
	private:
		void putZero(uInt i, uInt j, uInt pivot);	//pone el cero en esa posicion
		bool zeroDiag(uInt i);						//si la posicion ii tiene un cero
		uInt maxUnderDiag(uInt j) 					//estrategia de pivoteo parcial
		
		T    normInf();
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

#endif
