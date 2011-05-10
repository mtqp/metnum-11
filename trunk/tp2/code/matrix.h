#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "includes.h"
#include "vector.h"
#include "matrix_base.h"
#include "matrix_exceptions.h"

enum MatrixType{
	ID,
	TSup,
	TInf,
	Nula,
	Diag,
	Rand,
	BadK,
	Hilbert
};

/*
	NOTA: 
		- Utilizar try catch para manejar casos bordes
		- Si se acude a metodos auxiliares, mientras no este implementado tirar excepcion de no implementado
	
*/

template <class T>
class Matrix : public MatrixBase<T>{
	public:
		Matrix(uInt dim);
		Matrix(const Matrix<T>& mCopy);
		Matrix(T** data, uInt dim);
		Matrix(const T* data, uInt dim);
		Matrix(uInt dim, MatrixType type);
		~Matrix();
		
		Matrix<T> gaussianElim() const;						
		Matrix<T> LU() 		const;		
		Matrix<T> inverse() const;							
		T det() const;										
		
		bool isTriang(bool superior) const;
		bool isId() const;
		
		T K() const;
		
		Matrix<T>& operator= (const MatrixBase<T> &mb);
		
	private:
		void Gauss_LU(bool L);
		T coefficient(uInt i, uInt j);
		void putZero(uInt i, uInt j, T coefficient);		//pone el cero en esa posicion
		uInt maxUnderDiag(uInt j) const;					//estrategia de pivoteo parcial
		T  	 normF() const;
		
		void createId(uInt dim);
		void createBadK(uInt dim);
		void createHilbertMatrix(uInt dim);
};

template <typename T>
Matrix<T> :: Matrix(uInt dim) : MatrixBase<T>(dim,dim){}

template <typename T>
Matrix<T> :: Matrix(const Matrix<T>& mCopy) : MatrixBase<T>(mCopy){}

template <typename T>
Matrix<T> :: Matrix(T** data, uInt dim) : MatrixBase<T>(data,dim,dim){} 

template <typename T>
Matrix<T> :: Matrix(const T* data, uInt dim) : MatrixBase<T>(dim,dim) {
	int h = 0;

	for(int i=1;i<=dim;i++)
		for(int j=1;i<=dim;j++){
			this->setValue(data[h],i,j);
			h++;
		}
}

template <typename T>
Matrix<T> :: Matrix(uInt dim, MatrixType type) : MatrixBase<T>(dim, dim){
	switch(type){
		case(ID):
			createId(dim);
			break;
		case(BadK):
			createBadK(dim);
			break;
		case(Hilbert):
			createHilbertMatrix(dim);
			break;
		default:
			throw MatrixException((char*)"No implementadas... HACERLAS!");
	}
}

template <typename T>
Matrix<T> :: ~Matrix(){}

template <typename T>
Matrix<T> Matrix<T> :: gaussianElim() const {
	Matrix<T> copy(*this);
	copy.Gauss_LU(false);
	return copy;
}

/*	Devuelve una matriz la cual se interpreta: L abajo de la diagonal, U arriba de la diagonal y la diagonal */
template <typename T>
Matrix<T> Matrix<T> :: LU() const{
	Matrix<T> copy(*this);
	copy.Gauss_LU(true);
	return copy;
}

template <typename T>
Matrix<T> Matrix<T> :: inverse() const{
	if(!this->isInversible()) throw MatrixException((char*)"No existe la inversa");

	Matrix<T> copy(*this);
	
	uInt dim = this->getFiDimension();
	Matrix<T> I(dim,ID);
	
	uInt maxCol;
	T coefficient;
	
	for(int j=1; j<dim; j++){
		maxCol = copy.maxUnderDiag(j);
		if(copy.getValue(maxCol,j)!=0){			//si es cero se pasa a la otra columna, ya esta lo que queremos
			copy.swapFi(j,maxCol);
			I.swapFi(j,maxCol);
			for(int i=j+1; i<=dim; i++){
				coefficient = copy.coefficient(i,j);
				copy.putZero(i,j,coefficient);
				I.putZero(i,j,coefficient);
			}
		}
	}
	
	/* Aca no hay ceros en la diagonal, sino la matriz no seria inversible. No uso pivoteo parcial para no arruinar los ceros que ya consegui abajo de la diagonal */
	for(int j=dim; j>1; j--){
		if(copy.getValue(j,j)==0) throw MatrixException((char*)"Error no deberia haber ceros en la diagonal");
		for(int i=1; i<j; i++){
			coefficient = copy.coefficient(i,j);
			copy.putZero(i,j,coefficient);
			I.putZero(i,j,coefficient);
		}
	}
	
	T elemDiag;
	T elem;
	
	/*Pone unos en la diagonal para llegar a la identidad, modifica solo la matriz resultante*/
	for(int i=1; i<=dim; i++){
		elemDiag = copy.getValue(i,i);
		for(int j=1; j<=dim; j++){
			elem = I.getValue(i,j);
			elem /= elemDiag;
			I.setValue(elem,i,j);
		}
	}
			
	return I;
}

template <typename T>
T Matrix<T> :: det() const{
	Matrix<T> copy(*this);
	
	if(!this->isTriang(true) && !this->isTriang(false)){
		copy = this->gaussianElim();
	}
	
	uInt dim = copy.getFiDimension();
	T aux;
	T det = 1;
	for(int i=1; i<=dim; i++){
		aux = copy.getValue(i,i);
		if(aux==0) return 0;
		det *= aux;
	}
	
	return det;
}

template <typename T>
bool Matrix<T> :: isTriang(bool superior) const {
	bool res = true;
	uInt dim = MatrixBase<T> :: getFiDimension();
	
	if(superior){
		for(int i=2; i<=dim; i++)
			for(int j=1; j<i; j++)
				res &= this->getValue(i,j)==0;
	}
	else{
		for(int i=1; i<dim; i++)
			for(int j=i+1; j<=dim; j++)
				res &= this->getValue(i,j)==0;
	}
	
	return res;
}

template <typename T>
bool Matrix<T> :: isId() const {
	bool res = true;
	uInt dim = MatrixBase<T> :: getFiDimension();
	
	for(int i=1; i<=dim; i++)
		for(int j=1; j<=dim; j++)
			res &= (i==j && this->getValue(i,j)==1) || (i!=j && this->getValue(i,j)==0);
			
	return res;
}


template <typename T>
T Matrix<T> :: K() const{
	uInt dim = this->getFiDimension();
	Matrix<T> Inverse(dim);
	Inverse = this->inverse();
	T k = Inverse.normF();
	k *= this->normF();
	return k;
}

template <typename T>
Matrix<T>& Matrix<T> :: operator= (const MatrixBase<T> &mb){
	if(!this->matchExactDimesions(mb))
		throw MatrixException((char*)"Asignacion de matrices de diferente dimension)");

	uInt dim = this->getFiDimension();

	for(int i=1; i<=dim; i++)
		for(int j=1;j<=dim;j++)
			this->setValue(mb.getValue(i,j),i,j);
	
	return *this;
}

template <typename T>
void Matrix<T> :: Gauss_LU(bool L){
	uInt dim = MatrixBase<T> :: getFiDimension(); 
	uInt maxCol=0;
	T coefficient;
	
	for(int j=1; j<=dim; j++){
		maxCol = this->maxUnderDiag(j);
		if(this->getValue(maxCol,j)!=0){			//si es cero se pasa a la otra columna, ya esta lo que queremos
			this->swapFi(j,maxCol);
			for(int i=j+1; i<=dim; i++){
				coefficient = this->coefficient(i,j);
				this->putZero(i,j,coefficient);
				if(L) setValue(coefficient,i,j);
			}
		}
	}
}

template <typename T>
T Matrix<T> :: coefficient(uInt i, uInt j){
	T pivot = this->getValue(j,j);
	if(pivot==0)
		throw MatrixException((char*)"El pivot es cero.");
	
	pivot = this->getValue(i,j)/pivot;
	
	return pivot;
}

/* Esta funcion afecta toda la fila de la matriz donde se quiere poner el cero para que sirva tanto para triangular abajo como arriba de la diagonal, funciona siempre y cuando los ceros se vayan poniendo en orden */
template <typename T>
void Matrix<T> :: putZero(uInt i, uInt j, T coefficient){
	uInt dimCol = MatrixBase<T> :: getColDimension();
	T elem;
	
	for(int k=1; k<=dimCol; k++){
		elem = coefficient*this->getValue(j,k);
		elem = this->getValue(i,k) - elem; 
		this->setValue(elem,i,k);
	}
}

template <typename T>
uInt Matrix<T> :: maxUnderDiag(uInt j) const{
	uInt dim = MatrixBase<T> :: getFiDimension();
	
	if(j==0 || j>dim)
		throw MatrixException((char*)"El indice no pertenece a la diagonal, no esta en rango.");
	
	T pivot = abs(this->getValue(j,j));
	uInt pivot_pos = j;
	
	for(int i=j+1; i<=dim; i++){
		T elem = abs(this->getValue(i,j));
		if(elem>pivot){
			pivot = elem;
			pivot_pos = i;
		}
	}

	return pivot_pos;
}

template <typename T>
T Matrix<T> :: normF() const {
	uInt dim = MatrixBase<T> :: getFiDimension();
	
	T normF = this->getValue(1,1);
	
	if(dim==1) return normF;

	for(int i=1; i<=dim; i++)
		for(int j=1; j<=dim; j++)
			normF += this->getValue(i,j)*this->getValue(i,j);
	
	normF -= this->getValue(1,1);
	return sqrt(normF);
}

template <typename T>
void Matrix<T> :: createId(uInt dim){
	for(int i=1;i<=dim;i++)
		this->setValue((T) 1, i,i);
}

template <typename T>
void Matrix<T> :: createBadK(uInt dim) {
	if(rand()%2){
		//matrix de hilbert por un coef
		double randomCoef = rand()%10;//ajustar ese modulo
		Matrix<double> bad_conditioned(dim, Hilbert);
		randomCoef * bad_conditioned;
	}
	else 
	{
		//matriz con casi filas ld
		double epsilon = 1.0/1000.0;
	
		Vector<T> randomV(dim);
		randomV.createRandomVector();
	
		for(int i=1;i<=dim;i++)
			for(int j=1;j<=dim;j++){
				this->setValue(/*seed+j*/randomV.getValue(j),i,j);
				if(i==j){
					this->setValue(/*seed+j*/randomV.getValue(j)+epsilon,i,j);	
				}
			}
	}
}

/* Matriz de Hilbert de orden dim */
template <typename T>
void Matrix<T> :: createHilbertMatrix(uInt dim){
	T elem;
	
	for(int i=1; i<=dim; i++)
		for(int j=1; j<=dim; j++){
			elem = 1;
			elem /= (i+j-1);
			this->setValue(elem,i,j);
		}
}

#endif
