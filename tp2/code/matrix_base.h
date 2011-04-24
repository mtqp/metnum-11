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

		void fill(T value, uInt i, uInt j);

		bool isInversible();
		bool isSquare();
		virtual int  det();
	
		void inverse();
	
		void show();
//	protected:
	
	private:
		uInt _dimFi;
		uInt _dimCol;
		T** _matrix;
};


template <typename T>
MatrixBase<T> :: MatrixBase(uInt dimFi, uInt dimCol){
	_dimFi = dimFi;
	_dimCol= dimCol;
	
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
void MatrixBase<T> :: fill(T value, uInt i, uInt j){
	//fills the fucking matrix
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
/*virtual*/ int MatrixBase<T> :: det(){
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

template <typename T>
void MatrixBase<T> :: show(){
	cout << "implementar un lindo show de matrices" << endl;
}



#endif
