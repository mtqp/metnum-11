#ifndef __MATRIX_BASE_H__
#define __MATRIX_BASE_H__

#include "includes.h"
#include "matrix_exceptions.h"


/*
	PASAR TODO X REFERENCIA!!
*/


/*
	Quien herede de MatrixBase deberá atrapar las excepciones lanzadas
*/
template <class T>		//esto qdo asperisimo, pero sino revienta cuando quiere compilar
class MatrixBase;		//aparentemente ve el friend primero q la definicion...
template <typename T>
ostream &operator<< (ostream &stream, MatrixBase<T> mb);

template <class T>
class MatrixBase{
	public:
		MatrixBase(uInt dimFi, uInt dimCol);
		MatrixBase(T** data, uInt dimFi, uInt dimCol); 
		~MatrixBase();

		MatrixBase<T> operator+ (const MatrixBase<T> &mb);
		MatrixBase<T> operator- (const MatrixBase<T> &mb);
		MatrixBase<T> operator* (const MatrixBase<T> &mb);
		MatrixBase<T>& operator= (const MatrixBase<T> &mb);
		bool operator==(const MatrixBase<T> &mb);

		void setValue(T value, uInt i, uInt j);
		T&   getValue(uInt i, uInt j);

		bool isInversible();
		bool isSquare();

		virtual T det();	///Se calcula recursivamente -- NO triangula
	
		friend ostream &operator<< <>(ostream &stream, MatrixBase<T> mb);
		
		static MatrixBase<T> scalarMult(const T& value, /*const*/ MatrixBase<T> &mb);
		
	protected:
		int  getFiDimension() const;
		int  getColDimension() const;
		bool matchExactDimesions(const MatrixBase<T> &mb);
		bool matchMultDimesions(const MatrixBase<T> &mb);
		MatrixBase<T> deleteFi(uInt i);
		MatrixBase<T> deleteCol(uInt j);
		MatrixBase<T> deleteFiCol(uInt i, uInt j);
			
	private:
		void setMatrix(uInt dimFi, uInt dimCol);
		void multiplyFiCol(int fiI, int colJ, MatrixBase<T> A, MatrixBase<T> B);
		
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
	for(int i=0; i<_dimFi; i++)
		for(int j=0;j<_dimCol;j++)
			_matrix[i][j] = data[i][j];	
}

///trae seg fault... no se xq, mirar dsp!
template <typename T>
MatrixBase<T> :: ~MatrixBase(){
/*	for(int i=0;i<_dimFi; i++)
		delete [] _matrix[i];
		
	delete [] _matrix;*/
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: operator+ (const MatrixBase<T> &mb){
	if(!matchExactDimesions(mb))
		throw MatrixException((char*)"Suma de matrices de distinta dimension.");
	
	MatrixBase<T> resultSum(this->_dimFi,this->_dimCol);
	
	for(int i=0;i<_dimFi;i++)
		for(int j=0;j<_dimCol;j++)
			resultSum._matrix[i][j] = this->_matrix[i][j] + mb._matrix[i][j];

	return resultSum;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: operator- (const MatrixBase<T> &mb){
	if(!matchExactDimesions(mb))
		throw MatrixException((char*)"Resta de matrices de distinta dimension.");
	
	MatrixBase<T> resultSub(this->_dimFi,this->_dimCol);
	
	for(int i=0;i<_dimFi;i++)
		for(int j=0;j<_dimCol;j++)
			resultSub._matrix[i][j] = this->_matrix[i][j] - mb._matrix[i][j];

	return resultSub;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: operator* (const MatrixBase<T> &mb){
	if(!matchExactDimesions(mb))
		throw MatrixException((char*)"Multiplicación con incorrecta dimensiones.");
	
	MatrixBase<T> resultMult(this->_dimFi,mb._dimCol);	//esta bien no?

	for(int i=0;i<this->_dimFi;i++){
		for(int j=0;j<mb._dimCol;j++){
			resultMult.multiplyFiCol(i,j,*this, mb);
		}
	}
	
	return resultMult;
}

template <typename T>
MatrixBase<T> operator* (const T& value, MatrixBase<T> &mb){
	return MatrixBase<T> :: scalarMult(value,mb);
}

template <typename T>
MatrixBase<T> operator* (MatrixBase<T> &mb, const T& value){
	return MatrixBase<T> :: scalarMult(value,mb);
}

template <typename T>
bool MatrixBase<T> :: operator==(const MatrixBase<T> &mb){
	if(!matchExactDimension(mb))
		return false;
	
	bool eq = true;

	for(int i=0; i<this->_dimFi && eq; i++)
		for(int j=0; j<this->_dimCol && eq; j++)
			eq = this->_matrix[i][j] == mb._matrix[i][j];
	
	return eq;
}

///NOTA: no se hace un memcpy xq generaria alias, y no se si es eso lo q buscamos.
template <typename T>
MatrixBase<T>& MatrixBase<T> :: operator= (const MatrixBase<T> &mb){
	if(this!=&mb){
		if(!matchExactDimesions(mb))
			throw MatrixException((char*)"Asignacion de matrices de distinta dimension");
	
		for(int i=0; i<this->_dimFi; i++)
			for(int j=0;j<_dimCol;j++)
				this->_matrix[i][j] = mb._matrix[i][j];	
	}
	
	return *this;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: scalarMult(const T& value, /*const*/ MatrixBase<T> &mb){
	MatrixBase<T> scalarMultMatrix(mb._dimFi,mb._dimCol);

	for(int i=0; i<mb._dimFi; i++)
		for(int j=0;j<mb._dimCol;j++)
			scalarMultMatrix._matrix[i][j] = value * mb._matrix[i][j];

	return scalarMultMatrix;	
}

template <typename T>
void MatrixBase<T> :: setValue(T value, uInt i, uInt j){
	_matrix[i][j] = value;
}

template <typename T>
T& MatrixBase<T> :: getValue(uInt i, uInt j){
	if(i==0 || i>_dimFi)
		throw MatrixException((char*)"GetValue --> fila cero o inexistente");
	if(j==0 || j>_dimCol)
		throw MatrixException((char*)"GetValue --> columna cero o inexistente");
		
	return this->_matrix[i-1][j-1];
}

template <typename T>
bool MatrixBase<T> :: isInversible(){
	return det()!=0;	//T tiene q tener definido la desigualdad contra int!
}

template <typename T>
bool MatrixBase<T> :: isSquare(){
	return _dimFi == _dimCol;
}

template <typename T>
T MatrixBase<T> :: det(){
	if(!isSquare())
		throw MatrixException((char*)"Calculo de determinante en matriz cuadrada.");
	
	if(_dimFi==1)					//Caso base
		return this->_matrix[0][0];
	
	if(_dimFi==2 && _dimCol==2){	//Caso base
		return (_matrix[0][0]*_matrix[1][1]) - (_matrix[0][1]*_matrix[1][0]);
	}

	int determinante = 0;

	for(int i=1;i<=_dimFi;i++)		//Caso recursivo
		for(int j=1;j<=_dimCol;j++){
			MatrixBase<T> subMatrix(this->_dimFi-1,this->_dimCol-1);
			subMatrix = this->deleteFiCol(i,j);

			T subDet = this->_matrix[i-1][j-1] * subMatrix.det();
			determinante = determinante + subDet;
		}
	
	return determinante;
}


template <typename T>
ostream &operator<< (ostream &stream, MatrixBase<T> mb){
  stream << "IMPLEMENTACION TRIVIAL - pensar si hay alguna mejor" << endl;
  stream << "Dimension Filas = " << mb._dimFi << endl;
  stream << "Dimension Columnas = " << mb._dimCol << endl;
  
  for(int i=0; i<mb._dimFi; i++){
  	stream << endl;
  	for(int j=0; j<mb._dimCol; j++){
  		stream << mb._matrix[i][j] << "\t";
  	}
  }
  
  stream << endl;
  return stream; 
}

template <typename T>
int  MatrixBase<T> :: getFiDimension() const {
	return _dimFi;
}

template <typename T>
int  MatrixBase<T> :: getColDimension() const {
	return _dimCol;
}


template <typename T>
bool MatrixBase<T> :: matchExactDimesions(const MatrixBase<T> &mb){
	return (this->_dimFi==mb._dimFi) && (this->_dimCol==mb._dimCol);
}

template <typename T>
bool MatrixBase<T> :: matchMultDimesions(const MatrixBase<T> &mb){
	return this->_dimCol == mb._dimFi;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: deleteFi(uInt fiElim){
	if(fiElim==0 || fiElim>_dimFi)
		throw MatrixException((char*)"Se desea eliminar fila NO existente");
	
	fiElim--;	//Recordar que los arreglos son [0,...n-1], nosotros pasamos [1,...,n]
	
	//QUE HACEMOS SI TIENE SOLO UNA FILA Y SE LA ELIMINA?
	
	MatrixBase<T> deletedFi(_dimFi-1,_dimCol);
	
	for(int i=0; i<deletedFi._dimFi; i++){
		if(i<fiElim){
			for(int j=0;j<_dimCol;j++){
				deletedFi._matrix[i][j] = this->_matrix[i][j];
			}
		}
		else 
		{
			for(int j=0;j<_dimCol;j++){
				deletedFi._matrix[i][j] = this->_matrix[i+1][j];
			}
		}
	}
	
	return deletedFi;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: deleteCol(uInt colElim){
	if(colElim==0 || colElim>_dimCol)
		throw MatrixException((char*)"Se desea eliminar columna NO existente");
		
	//QUE HACEMOS SI TIENE SOLO UNA COLUMNA Y SE LA ELIMINA?
	
	MatrixBase<T> deletedCol(_dimFi,_dimCol-1);
	
	colElim--;	//Recordar que los arreglos son [0,...n-1], nosotros pasamos [1,...,n]
	
	//se itera por columna, es mucho menos eficiente, importa?
	for(int j=0;j<deletedCol._dimCol;j++){
		if(j<colElim){
			for(int i=0; i<this->_dimFi; i++){
				deletedCol._matrix[i][j] = this->_matrix[i][j];
			}
		}
		else 
		{
			for(int i=0; i<this->_dimFi; i++){
				deletedCol._matrix[i][j] = this->_matrix[i][j+1];
			}
		}
	}
	
	return deletedCol;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: deleteFiCol(uInt i, uInt j){
	if(i==0 || i>_dimFi)
		throw MatrixException((char*)"Se desea eliminar fila NO existente");
	if(j==0 || j>_dimCol)
		throw MatrixException((char*)"Se desea eliminar columna NO existente");

	MatrixBase<T> delFi(_dimFi-1,_dimCol);
	delFi = this->deleteFi(i);
	
	MatrixBase<T> delCol(delFi._dimFi,_dimCol-1); 
	delCol = delFi.deleteCol(j);
	
	return delCol;
}

template <typename T>
void MatrixBase<T> :: setMatrix(uInt dimFi, uInt dimCol){
	_dimFi = dimFi;
	_dimCol= dimCol;
	
	if(_dimFi==0 || _dimCol==0)
		throw MatrixException((char*)"Las dimensiones de la matriz deben ser mayores a cero");
	
	_matrix = new T* [_dimFi];

    for (int i=0; i<_dimFi; i++){
      	_matrix[i] = new T [_dimCol];
     	for(int j=0; j<_dimCol; j++){
     		memset((void*) &_matrix[i][j],0,sizeof(T));
     	}
     }
}

template <typename T>
void MatrixBase<T> :: multiplyFiCol(int fiI, int colJ, MatrixBase<T> A, MatrixBase<T> B){
	for(int i=0; i<A._dimCol; i++){
		this->_matrix[fiI][colJ] = this->_matrix[fiI][colJ] + (A._matrix[fiI][i] * B._matrix[i][colJ]);
	}
}

#endif
