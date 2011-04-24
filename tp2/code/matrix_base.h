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
		MatrixBase(T** data, uInt dimFi, uInt dimCol); 
		~MatrixBase();

		MatrixBase<T> operator+ (const MatrixBase<T> &mb);
		MatrixBase<T> operator* (const MatrixBase<T> &mb);
		MatrixBase<T>& operator= (const MatrixBase<T> &mb);

		void setValue(T value, uInt i, uInt j);

		bool isInversible();
		bool isSquare();

		virtual int  det();	///Se calcula recursivamente -- NO triangula
//		void inverse();
	
		friend ostream &operator<< <T>(ostream &stream, MatrixBase<T> mb);
		
	protected:
		bool matchExactDimesions(MatrixBase<T> &mb);
		bool matchMultDimesions(MatrixBase<T> &mb);
		MatrixBase<T> deleteFi(uInt i);
		MatrixBase<T> deleteCol(uInt j);
			
	private:
		void setMatrix(uInt dimFi, uInt dimCol);
		
		uInt _dimFi;
		uInt _dimCol;
		T** _matrix;
};


template <typename T>
MatrixBase<T> :: MatrixBase(uInt dimFi, uInt dimCol){
	setMatrix(dimFi,dimCol);
}

template <typename T>
MatrixBase<T> :: MatrixBase(T** data, uInt dimFi, uInt dimCol){
	setMatrix(dimFi,dimCol);
	
	///Copia la estructura en vez de hacer alias <==> T no genera alias en la asignacion
	for(int i=0; i<this->_dimFi; i++)
		for(int j=0;j<_dimCol;j++)
			this->_matrix[i][j] = data[i][j];	
	
}

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
	
	MatrixBase<T> resultSum(this->_dimFi,this->_dimCol);
	
	for(int i=0;i<_dimFi;i++)
		for(int j=0;j<_dimCol;j++)
			resultSum._matrix[i][j] = this->_matrix[i][j] + mb._matrix[i][j];

	return resultSum;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: operator* (const MatrixBase<T> &mb){
	if(!matchMultDimensions(mb))
		throw new MatrixException("Multiplicación con incorrecta dimensiones.");
	
	MatrixBase<T> resultMult(this->_dimFi,mb._dimCol);	//esta bien no?
	
	for(int i=0;i<_dimFi;i++)
		for(int j=0;j<_dimCol;j++)	//creeria q el algo de multiplicacion esta bien, CHKear x las dudas
			resultMult._matrix[i][j] = resultMult._matrix[i][j] + (this->_matrix[i][j] * mb._matrix[j][i]);

	return resultMult;
}

///NOTA: no se hace un memcpy xq generaria alias, y no se si es eso lo q buscamos.
template <typename T>
MatrixBase<T>& MatrixBase<T> :: operator= (const MatrixBase<T> &mb){
	if(this!=&mb){
		if(!matchExactDimensions(mb))
			throw new MatrixException("Asignacion de matrices de distinta dimension");
	
		for(int i=0; i<this->_dimFi; i++)
			for(int j=0;j<_dimCol;j++)
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
int MatrixBase<T> :: det(){
	//calculamos el determinante recursivamente, y el q genere las triangulaciones lo sobreescriba
	if(!isSquare())
		throw new MatrixException("Calculo de determinante en matriz cuadrada.");
	
	if(_dimFi==2 && _dimCol==2){
		//esto devuelve algo de tipo T... como lo soluciono?!?!?!
		//return (_matrix[0][0]*_matrix[1][1]) - (_matrix[0][1]*_matrix[1][0])
		return -1234;
	}

	int determinante = 0;

	for(int i=0;i<_dimFi;i++)
		for(int j=0;j<_dimCol;j++){
//			ARREGLAR!
			MatrixBase<T> subMatrix(1,1); // = FUCK!
			subMatrix.det();
		}
	

	return determinante;
}

/*
template <typename T>
void MatrixBase<T> :: inverse(){
	if(!isInversible())
		throw new MatrixException("No inversible.");
		
	///Tiene sentido que aca dentro calculemos la inversa? NO ESTOY SEGURO
}
*/

template <typename T>
ostream &operator<< (ostream &stream, MatrixBase<T> mb){
  stream << "HAY Q IMPLMENTARLO --> No se si la implementacion trivial sirve si la matriz es muy grande.";
  return stream; 
}


template <typename T>
bool MatrixBase<T> :: matchExactDimesions(MatrixBase<T> &mb){
	return (this->_dimFi==mb._dimFi) && (this->_dimCol==mb._dimCol);
}

template <typename T>
bool MatrixBase<T> :: matchMultDimesions(MatrixBase<T> &mb){
	return this->_dimCol == mb._dimFi;
}

//no me gusta como esta implementado... pensar si se puede hacer mejor.
//vendria mejor q elimine tanto una fila como una columna... pasa q capas lo de las filas sirve para cuando
//factoricemos y una fila se vaya! no se... pensar...
template <typename T>
MatrixBase<T> MatrixBase<T> :: deleteFi(uInt fiElim){
	if(fiElim==0 || fiElim>_dimFi)
		throw new MatrixException("Se desea eliminar fila NO existente");
	
	//QUE HACEMOS SI TIENE SOLO UNA FILA Y SE LA ELIMINA?
	
	MatrixBase<T> deletedFi(_dimFi-1,_dimCol);
	
	for(int i=0; i<deletedFi._dimFi; i++){
		if(i<fiElim){
			for(int j=0;j<_dimCol;j++){
				deletedFi[i][j] = this->_matrix[i][j];
			}
		}
		else 
		{
			for(int j=0;j<_dimCol;j++){
				deletedFi[i][j] = this->_matrix[i+1][j];
			}
		}
	}
	
	return deletedFi;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: deleteCol(uInt colElim){
	if(colElim==0 || colElim>_dimCol)
		throw new MatrixException("Se desea eliminar columna NO existente");
		
	//QUE HACEMOS SI TIENE SOLO UNA COLUMNA Y SE LA ELIMINA?
	
	MatrixBase<T> deletedCol(_dimFi,_dimCol-1);
	
	//se itera por columna, es mucho menos eficiente, importa?
	for(int j=0;j<deletedCol._dimCol;j++){
		if(j<colElim){
			for(int i=0; i<this->_dimFi; i++){
				deletedCol[i][j] = this->_matrix[i][j];
			}
		}
		else 
		{
			for(int i=0; i<this->_dimFi; i++){
				deletedCol[i][j] = this->_matrix[i][j+1];
			}
		}
	}
	
	return deletedCol;
}

template <typename T>
void MatrixBase<T> :: setMatrix(uInt dimFi, uInt dimCol){
	_dimFi = dimFi;
	_dimCol= dimCol;
	
	if(_dimFi==0 || _dimCol==0)
		throw new MatrixException("Las dimensiones de la matriz deben ser mayores a cero");
	
	_matrix = new T* [_dimFi];

    for (int i=0; i<_dimFi; i++)
      _matrix[i] = new T [_dimCol];
}

#endif
