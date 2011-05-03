#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "includes.h"
#include "matrix_base.h"
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
		Matrix(const Matrix<T>& mCopy);
		Matrix(T** data, uInt dimFi, uInt dimCol);
		Matrix(uInt dimFi, uInt dimCol, MatrixType type);	//IMPLEMENTAR (Mañana lo hago!)
		~Matrix();
		
		Matrix<T> gaussianElim() const;						//IMPLEMENTAR
		Matrix<T> LU() 		const; //o QR no sabemos		//IMPLEMENTAR
		Matrix<T> inverse() const;							//IMPLEMENTAR
		T det() const;										//IMPLEMENTAR
		
		bool isTriang(bool superior) const;
		bool isId() const;
		
		T K();	//no deberia devolver doubles?				//IMPLEMENTAR
		
		Matrix<T>& operator= (const MatrixBase<T> &mb);
		
	private:
		void putZero(uInt i, uInt j);				//pone el cero en esa posicion
		bool zeroDiag(uInt i);						//si la posicion ii tiene un cero
		uInt maxUnderDiag(uInt j); 					//estrategia de pivoteo parcial
		
		T  	 normF() const;	//no deberia devolver doubles?
};

template <typename T>
Matrix<T> :: Matrix(uInt dimFi, uInt dimCol) : MatrixBase<T>(dimFi,dimCol){}

template <typename T>
Matrix<T> :: Matrix(const Matrix<T>& mCopy) : MatrixBase<T>(mCopy){
}

template <typename T>
Matrix<T> :: Matrix(T** data, uInt dimFi, uInt dimCol) : MatrixBase<T>(data,dimFi,dimCol) {} 

template <typename T>
Matrix<T> :: Matrix(uInt dimFi, uInt dimCol, MatrixType type) : MatrixBase<T>(dimFi, dimCol){
	throw MatrixException((char*)"Generador NO implementado");
}

template <typename T>
Matrix<T> :: ~Matrix(){}

template <typename T>
Matrix<T> Matrix<T> :: gaussianElim() const {
	throw MatrixException((char*)"Eliminacion gaussiana no implementada");
}

template <typename T>
Matrix<T> Matrix<T> :: LU() const{
	throw MatrixException((char*)"Factorizacion LU no implementada");
}

template <typename T>
Matrix<T> Matrix<T> :: inverse() const{
	throw MatrixException((char*)"Inversa no implementada");
}

template <typename T>
T Matrix<T> :: det() const{
	throw MatrixException((char*)"DET no recursivo no implementado");
}

template <typename T>
bool Matrix<T> :: isTriang(bool superior) const {
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
bool Matrix<T> :: isId() const {
	bool res = true;
	uInt dimFi = MatrixBase<T> :: getFiDimension();
	uInt dimCol = MatrixBase<T> :: getColDimension();
	
	for(int i=1; i<=dimFi; i++)
		for(int j=1; j<=dimCol; j++)
			res &= (i==j && this->getValue(i,j)==1) || (i!=j && this->getValue(i,j)==0);
			
	return res;
}


template <typename T>
T Matrix<T> :: K(){
	throw MatrixException((char*)"nro condicion no implementado");
}

template <typename T>
Matrix<T>& Matrix<T> :: operator= (const MatrixBase<T> &mb){
	if(!this->matchExactDimesions(mb))
		throw MatrixException((char*)"Asignacion de matrices de diferente dimension)");

	uInt dimFi = this->getFiDimension();
	uInt dimCol= this->getColDimension();

	for(int i=1; i<=dimFi; i++)
		for(int j=1;j<=dimCol;j++)
			this->setValue(mb.getValue(i,j),i,j);
	
	return *this;
}

template <typename T>
void Matrix<T> :: putZero(uInt i, uInt j){
	T pivot = this->getValue(j,j);
	if(pivot==0)
		throw MatrixException((char*)"El pivot es cero.");
	
	pivot = this->getValue(i,j)/pivot;
	
	cout << "pivot" << pivot << endl;
	
	uInt dimCol = MatrixBase<T> :: getColDimension();
	
	for(int k=j; k<=dimCol; k++){
		T elem = this->getValue(i,k)-pivot*this->getValue(j,k);
		this->setValue(elem,i,k);
	}
	
}

template <typename T>
uInt Matrix<T> :: maxUnderDiag(uInt j){
	uInt dimFi = MatrixBase<T> :: getFiDimension();
	uInt dimCol = MatrixBase<T> :: getColDimension();
	
	if(j==0 || j>dimFi || j>dimCol)
		throw MatrixException((char*)"El indice no pertenece a la diagonal, no esta en rango.");
	
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
T Matrix<T> :: normF() const {
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
