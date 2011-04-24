#ifndef __MATRIX_BASE_H__
#define __MATRIX_BASE_H__

#include "includes.h"
#include "matrix_exceptions.h"

/*
	Quien herede de MatrixBase deberá atrapar las excepciones lanzadas
*/

template <class T>
class MatrixBase{
	public:
		MatrixBase(uInt dimFi, uInt dimCol);
//		MatrixBase(T** data, uInt dimFi, uInt dimCol); //no se si es necesario,
		~MatrixBase();

		MatrixBase operator+ (const MatrixBase &mb);
		MatrixBase operator* (const MatrixBase &mb);
		MatrixBase& operator= (const MatrixBase &mb);

		void setValue(T value, uInt i, uInt j);

		bool isInversible();
		bool isSquare();

		virtual int  det();	//Se calcula recursivamente -- NO triangula
		void inverse();
	
//		friend ostream &operator<<(ostream &stream, MatrixBase mb);
	protected:
		bool matchExactDimesions(MatrixBase &mb);	//capas q van privates!!!
		bool matchMultDimesions(MatrixBase &mb);
			
	private:
		uInt _dimFi;
		uInt _dimCol;
		T** _matrix;
};


template <typename T>
MatrixBase<T> :: MatrixBase(uInt dimFi, uInt dimCol){
	_dimFi = dimFi;
	_dimCol= dimCol;
	
	if(_dimFi==0 || _dimCol==0)
		throw new MatrixException("Las dimensiones de la matriz deben ser mayores a cero");
	
	_matrix = new T* [_dimFi];

    for (int i=0; i<_dimFi; i++)
      _matrix[i] = new T [_dimCol];
}

//		MatrixBase(T** data, uInt dimFi, uInt dimCol); //no se si es necesario,

template <typename T>
MatrixBase<T> :: ~MatrixBase(){
	for(int i=0;i<_dimFi; i++)
		delete [] _matrix[i];
		
	delete [] _matrix;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: operator+ (const MatrixBase<T> &mb){
	if(!matchExactDimensions(mb))
		throw new MatrixException("Suma de matrices de distinta dimension.");
	
	MatrixBase<T> resultSum(this->_dimFi,this->_dimCol);	//hay q construirla en cero o algo? creo q no
	
	for(int i=0;i<_dimFi;i++)
		for(int j=0;j<_dimCol;i++)
			resultSum._matrix[i][j] = this->_matrix[i][j] + mb._matrix[i][j];

	return resultSum;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: operator* (const MatrixBase<T> &mb){
	if(!matchMultDimensions(mb))
		throw new MatrixException("Multiplicación con incorrecta dimensiones.");
	
	MatrixBase<T> resultMult(this->_dimFi,mb._dimCol);	//esta bien no?
	
	for(int i=0;i<_dimFi;i++)
		for(int j=0;j<_dimCol;i++)	//creeria q el algo de multiplicacion esta bien, CHKear x las dudas
			resultMult._matrix[i][j] = resultMult._matrix[i][j] + (this->_matrix[i][j] * mb._matrix[j][i]);

	return resultMult;
}

/*NOTA: no se hace un memcpy xq generaria alias, y no se si es eso lo q buscamos.*/
template <typename T>
MatrixBase<T>& MatrixBase<T> :: operator= (const MatrixBase<T> &mb){
	if(this!=&mb){
		if(!matchExactDimensions(mb))
			throw new MatrixException("Asignacion de matrices de distinta dimension");
	
		for(int i=0; i<this->_dimFi; i++)
			for(int j=0;j<_dimCol;i++)
				this->_matrix[i][j] = mb._matrix[i][j];	
	}
	
	return *this;
}


template <typename T>
void MatrixBase<T> :: setValue(T value, uInt i, uInt j){
	_matrix[i][j] = value;
}

template <typename T>
bool MatrixBase<T> :: isInversible(){
	return det()!=0;
}

template <typename T>
bool MatrixBase<T> :: isSquare(){
	return _dimFi == _dimCol;
}

template <typename T>
bool MatrixBase<T> :: matchExactDimesions(MatrixBase<T> &mb){
	return (this->_dimFi==mb._dimFi) && (this->_dimCol==mb._dimCol);
}
template <typename T>
bool MatrixBase<T> :: matchMultDimesions(MatrixBase<T> &mb){
	return this->_dimCol == mb._dimFi;
}

template <typename T>
int MatrixBase<T> :: det(){
	//calculamos el determinante recursivamente, y el q genere las triangulaciones lo sobreescriba
	if(!isSquare())
		throw new MatrixException("Calculo de determinante en matriz cuadrada.");
	
	//asdfasdf
	return -1;
}

template <typename T>
void MatrixBase<T> :: inverse(){
	if(!isInversible())
		throw new MatrixException("No inversible.");
		
	//adoifjoaidfjvo
}

/*
template <typename T>
ostream &operator<<(ostream &stream, MatrixBase mb){
  stream << "BLAH HAY Q IMPLMENTARLO";
  return stream; 
}
*/

#endif
