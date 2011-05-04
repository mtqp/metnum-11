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
		Matrix(uInt dim);
		Matrix(const Matrix<T>& mCopy);
		Matrix(T** data, uInt dim);
		Matrix(uInt dim, MatrixType type);	//IMPLEMENTAR (Mañana lo hago!)
		~Matrix();
		
		Matrix<T> gaussianElim() const;						
		Matrix<T> LU() 		const; //o QR no sabemos		
		Matrix<T> inverse() const;							//IMPLEMENTAR
		T det() const;										
		
		bool isTriang(bool superior) const;
		bool isId() const;
		
		T K() const;	//no deberia devolver doubles?				//IMPLEMENTAR
		
		Matrix<T>& operator= (const MatrixBase<T> &mb);
		
	private:
		void Gauss_LU(bool L);
		T coefficient(uInt i, uInt j);
		void putZero(uInt i, uInt j, T coefficient);		//pone el cero en esa posicion
		uInt maxUpDiag(uInt j) const;					//estrategia de pivoteo parcial
		uInt maxUnderDiag(uInt j) const;					//estrategia de pivoteo parcial
		T  	 normF() const;									//no deberia devolver doubles?
		
		void createId(uInt dim);
		void createBadK();
		void hilbertMatrix(T rMult);
		
		void setP(uInt dim);
		int* P;
};

template <typename T>
Matrix<T> :: Matrix(uInt dim) : MatrixBase<T>(dim,dim){
	setP(dim);
}

template <typename T>
Matrix<T> :: Matrix(const Matrix<T>& mCopy) : MatrixBase<T>(mCopy){
	uInt dim = this->getFiDimension();
	
	P = new int[dim];
	
	for(int i=0; i<dim; i++){
			this->P[i] = mCopy.P[i];
	}
}

template <typename T>
Matrix<T> :: Matrix(T** data, uInt dim) : MatrixBase<T>(data,dim,dim){
	setP(dim);
} 

template <typename T>
Matrix<T> :: Matrix(uInt dim, MatrixType type) : MatrixBase<T>(dim, dim){
	switch(type){
		case(ID):
			setP(dim);
			createId(dim);
			break;
		/*case(BadK):
			createBadK();
			break;*/
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

/* OJO!!! Anda si no necesita permutar!!! */
template <typename T>
Matrix<T> Matrix<T> :: inverse() const{
	if(!this->isInversible()) throw MatrixException((char*)"No existe la inversa");
	
	uInt dim = this->getFiDimension();
	Matrix<T> copy(*this);
	Matrix<T> id(dim,ID);
	uInt maxCol;
	T coefficient;
	
	for(int j=1; j<=dim; j++){
		maxCol = copy.maxUnderDiag(j);
		if(copy.getValue(maxCol,j)!=0){			//si es cero se pasa a la otra columna, ya esta lo que queremos
			copy.swapFi(j,maxCol);
			id.swapFi(j,maxCol);
			swap(copy.P[j-1],copy.P[maxCol-1]);
			swap(id.P[j-1],id.P[maxCol-1]);
			for(int i=j+1; i<=dim; i++){
				coefficient = copy.coefficient(i,j);
				copy.putZero(i,j,coefficient);
				id.putZero(i,j,coefficient);
			}
		}
	}
	
	for(int j=dim; j>1; j--){
		maxCol = this->maxUpDiag(j);
		if(this->getValue(maxCol,j)!=0){			//si es cero se pasa a la otra columna, ya esta lo que queremos
			copy.swapFi(j,maxCol);
			id.swapFi(j,maxCol);
			swap(copy.P[j-1],copy.P[maxCol-1]);
			swap(id.P[j-1],id.P[maxCol-1]);
			for(int i=1; i<j; i++){
				coefficient = copy.coefficient(i,j);
				copy.putZero(i,j,coefficient);
				id.putZero(i,j,coefficient);
			}
		}
	}
	
	T elemDiag;
	T elem;
	
	/*Pone unos en la diagonal para llegar a la identidad, modifica solo la matriz resultante*/
	for(int i=1; i<=dim; i++){
		elemDiag = copy.getValue(i,i);
		for(int j=1; j<=dim; j++){
			elem = id.getValue(i,j);
			elem /= elemDiag;
			id.setValue(elem,i,j);
		}
	}
	
	cout << "copy" << endl;
	cout << copy << endl;
	
	cout << "ID" << endl;
	cout << id << endl;

	cout << "P copy" << endl;
	for(int i=0; i<dim; i++)
		cout << copy.P[i] << ", ";
	cout << endl;

	
	
	return id;
}

template <typename T>
T Matrix<T> :: det() const{
	Matrix<T> copy(*this);
	
	if(!this->isTriang(true) && !this->isTriang(false)){
		copy = this->gaussianElim();
	}
	
	uInt dim = copy.getFiDimension();
	T det = copy.getValue(1,1);
	for(int i=2; i<=dim; i++)
		det *= copy.getValue(i,i);
	
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
	throw MatrixException((char*)"nro condicion no implementado");
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
			swap(this->P[j-1],this->P[maxCol-1]);
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

template <typename T>
void Matrix<T> :: putZero(uInt i, uInt j, T coefficient){
	uInt dimCol = MatrixBase<T> :: getColDimension();
	T elem;
	
	for(int k=j; k<=dimCol; k++){
		elem = coefficient*this->getValue(j,k);
		elem = this->getValue(i,k) - elem; 
		this->setValue(elem,i,k);
	}
}

template <typename T>
uInt Matrix<T> :: maxUpDiag(uInt j) const{
	uInt dim = MatrixBase<T> :: getFiDimension();
	
	if(j==0 || j>dim)
		throw MatrixException((char*)"El indice no pertenece a la diagonal, no esta en rango.");
	
	T pivot = abs(this->getValue(j,j));
	uInt pivot_pos = j;
	
	for(int i=j-1; i>=1; i--){
		T elem = abs(this->getValue(i,j));
		if(elem>pivot){
			pivot = elem;
			pivot_pos=i;
		}
	}

	return pivot_pos;
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
			pivot_pos=i;
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

/*
template <typename T>
void Matrix<T> :: createBadK(){
	srand(time(NULL));
	
	uInt randomSelector = 0;// rand()%3;
	
	switch(randomSelector){
		case(0):
			T rMul = (T) (rand()%100);
			hilbertMatrix(rMul);
			break;
		default:
			throw MatrixException((char*)"Not implemented BAD K");
	}
}

template <typename T>
void Matrix<T> :: hilbertMatrix(T rMult){
	T uno = (T) 1;
	T den = (T) uno;

	for(int i=1;i<=getFiDimension();i++)
		for(int j=1;j<=getColDimension();j++){
			setValue(rMult*(uno/den),i,j);
			den = den + 1;
		}
}
*/

template <typename T>
void Matrix<T> :: setP(uInt dim){
	P = new int[dim];
	for(int i=0; i<dim; i++)
		P[i]=i+1;
}

#endif
