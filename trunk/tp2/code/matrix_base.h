#ifndef __MATRIX_BASE_H__
#define __MATRIX_BASE_H__

#include "includes.h"
#include "matrix_exceptions.h"


#define protected public

/*
	Quien herede de MatrixBase deberá atrapar las excepciones lanzadas
*/

template <class T>		//esto qdo asperisimo, pero sino revienta cuando quiere compilar
class MatrixBase;		//aparentemente ve el friend primero q la definicion...
template <typename T>
ostream &operator<< (ostream &stream,const MatrixBase<T>& mb);

template <class T>
class MatrixBase{
	public:
		MatrixBase(uInt dimFi, uInt dimCol);
		MatrixBase(T** data, uInt dimFi, uInt dimCol); 
		MatrixBase(const MatrixBase<T>& mb);
		~MatrixBase();

		MatrixBase<T> operator+ (const MatrixBase<T> &mb) const;
		MatrixBase<T> operator- (const MatrixBase<T> &mb) const;
		MatrixBase<T> operator* (const MatrixBase<T> &mb) const;
		MatrixBase<T>& operator= (const MatrixBase<T> &mb);
		bool operator==(const MatrixBase<T> &mb) const;
		bool operator!=(const MatrixBase<T> &mb) const;

		MatrixBase<T> traspuesta() const;

		void setValue(T value, uInt i, uInt j);
		T    getValue(uInt i, uInt j) const;

		bool isInversible() const;
		bool isSquare() const;

		virtual T det() const;	///Se calcula recursivamente -- NO triangula (arreglar!!!!)
	
		friend ostream &operator<< <>(ostream &stream, const MatrixBase<T>& mb);
		
		static MatrixBase<T> scalarMult(const T& value, const MatrixBase<T> &mb);
		
	protected:
		uInt  getFiDimension()  const;
		uInt  getColDimension() const;
		bool matchExactDimesions(const MatrixBase<T> &mb) const;
		bool matchMultDimesions(const MatrixBase<T> &mb)  const;
		MatrixBase<T> deleteFi(uInt i) const;
		MatrixBase<T> deleteCol(uInt j)const;
		MatrixBase<T> deleteFiCol(uInt i, uInt j) const;
		MatrixBase<T>& swapFi(uInt i, uInt i2);
		MatrixBase<T>& swapCol(uInt j, uInt j2);
			
	private:
		void setMatrix(uInt dimFi, uInt dimCol);
		void multiplyFiCol(int fiI, int colJ, const MatrixBase<T>& A, const MatrixBase<T>& B);
		
		uInt _dimFi;
		uInt _dimCol;
		T** _matrix;
};

template <typename T>
MatrixBase<T> :: MatrixBase(uInt dimFi, uInt dimCol){
	setMatrix(dimFi,dimCol);
}

template <typename T>
MatrixBase<T> :: MatrixBase(const MatrixBase<T>& mb){
	setMatrix(mb._dimFi,mb._dimCol);

	for(int i=0; i<this->_dimFi; i++)
		for(int j=0;j<this->_dimCol;j++)
			this->_matrix[i][j] = mb._matrix[i][j];	
}

template <typename T>
MatrixBase<T> :: MatrixBase(T** data, uInt dimFi, uInt dimCol){
	setMatrix(dimFi,dimCol);
	
	///Copia la estructura en vez de hacer alias <==> T no genera alias en la asignacion
	for(int i=0; i<_dimFi; i++)
		for(int j=0;j<_dimCol;j++)
			_matrix[i][j] = data[i][j];	
}

template <typename T>
MatrixBase<T> :: ~MatrixBase(){
	for(int j=0;j<_dimFi; j++)
		delete [] _matrix[j];
		
	delete [] _matrix;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: operator+ (const MatrixBase<T> &mb) const {
	if(!matchExactDimesions(mb))
		throw MatrixException((char*)"Suma de matrices de distinta dimension.");
	
	MatrixBase<T> resultSum(this->_dimFi,this->_dimCol);

	for(int i=0;i<_dimFi;i++)
		for(int j=0;j<_dimCol;j++)
			resultSum._matrix[i][j] = this->_matrix[i][j] + mb._matrix[i][j];

	return resultSum;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: operator- (const MatrixBase<T> &mb) const {
	if(!matchExactDimesions(mb))
		throw MatrixException((char*)"Resta de matrices de distinta dimension.");
	
	MatrixBase<T> resultSub(this->_dimFi,this->_dimCol);
	
	for(int i=0;i<_dimFi;i++)
		for(int j=0;j<_dimCol;j++)
			resultSub._matrix[i][j] = this->_matrix[i][j] - mb._matrix[i][j];

	return resultSub;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: operator* (const MatrixBase<T> &mb) const {
	if(!matchMultDimesions(mb))
		throw MatrixException((char*)"Multiplicación con incorrecta dimensiones.");
	
	MatrixBase<T> resultMult(this->_dimFi,mb._dimCol);

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
bool MatrixBase<T> :: operator==(const MatrixBase<T> &mb) const {
	if(!matchExactDimesions(mb))
		return false;
	
	bool eq = true;

	for(int i=0; i<this->_dimFi && eq; i++)
		for(int j=0; j<this->_dimCol && eq; j++)
			eq = this->_matrix[i][j] == mb._matrix[i][j];
	
	return eq;
}

template <typename T>
bool MatrixBase<T> :: operator!=(const MatrixBase<T> &mb) const {
	return !(*this==mb);
}


template <typename T>
MatrixBase<T>& MatrixBase<T> :: operator= (const MatrixBase<T> &mb){
	if(this!=&mb){
		if(!matchExactDimesions(mb))
			throw MatrixException((char*)"Asignacion de matrices de distinta dimension");
	
		for(int i=0; i<mb._dimFi; i++)
			for(int j=0;j<mb._dimCol;j++)
				this->_matrix[i][j] = mb._matrix[i][j];	
	}
	
	return *this;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: traspuesta() const {
	MatrixBase<T> mt(this->_dimCol,this->_dimFi);
	for(int i=0; i<mt._dimFi; i++)
		for(int j=0;j<mt._dimCol;j++)
			mt._matrix[i][j] = this->_matrix[j][i];
	
	return mt;
}


template <typename T>
MatrixBase<T> MatrixBase<T> :: scalarMult(const T& value, const MatrixBase<T> &mb){
	MatrixBase<T> scalarMultMatrix(mb._dimFi,mb._dimCol);

	for(int i=0; i<mb._dimFi; i++)
		for(int j=0;j<mb._dimCol;j++)
			scalarMultMatrix._matrix[i][j] = value * mb._matrix[i][j];

	return scalarMultMatrix;	
}

template <typename T>
void MatrixBase<T> :: setValue(T value, uInt i, uInt j){
	if(i==0 || i>_dimFi || j==0 || j>_dimCol)
		throw MatrixException((char*)"SetValue -->Asignacion de valor en posicion inexistente");

	_matrix[i-1][j-1] = value;
}

template <typename T>
T MatrixBase<T> :: getValue(uInt i, uInt j) const {
	if(i==0 || i>_dimFi)
		throw MatrixException((char*)"GetValue --> fila cero o inexistente");
	if(j==0 || j>_dimCol)
		throw MatrixException((char*)"GetValue --> columna cero o inexistente");
		
	return this->_matrix[i-1][j-1];
}

template <typename T>
bool MatrixBase<T> :: isInversible() const {
	return det()!=0;	//T tiene q tener definido la desigualdad contra int!
}

template <typename T>
bool MatrixBase<T> :: isSquare() const {
	return _dimFi == _dimCol;
}

template <typename T>
T MatrixBase<T> :: det() const {
	if(!isSquare())
		throw MatrixException((char*)"Calculo de determinante en matriz cuadrada.");
	
	if(_dimFi==1)					//Caso base
		return this->_matrix[0][0];
	
	if(_dimFi==2 && _dimCol==2){	//Caso base
		return (_matrix[0][0]*_matrix[1][1]) - (_matrix[0][1]*_matrix[1][0]);
	}

	int determinante = 0;
	int i = 1;

	//for(int i=1;i<=_dimFi;i++)	{	//Caso recursivo
		for(int j=1;j<=_dimCol;j++){
			MatrixBase<T> subMatrix(this->_dimFi-1,this->_dimCol-1);
			subMatrix = this->deleteFiCol(i,j);
/*			cout << "----------------------------" << endl;
			if((i+j)%2 == 0)	//1^(i+j)
				cout << "SUMA" << endl;
			else
				cout << "resta!" << endl;
*/
			T subDet = this->_matrix[i-1][j-1] * subMatrix.det();
/*			cout << "elem a_I_J = " << this->_matrix[i-1][j-1] << endl;
			cout << "sub matrix i = " << i << " j = " << j << endl << subMatrix << "subDet = " << subDet << endl;;
			cout << "----------------------------" << endl;
*/
			if((i+j)%2 == 0)	//1^(i+j)
				determinante = determinante + subDet;
			else
				determinante = determinante - subDet;
		}
	//}
	
	return determinante;
}


template <typename T>
ostream &operator<< (ostream &stream, const MatrixBase<T>& mb){
///  stream << "IMPLEMENTACION TRIVIAL - pensar si hay alguna mejor" << endl;
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
uInt  MatrixBase<T> :: getFiDimension() const {
	return _dimFi;
}

template <typename T>
uInt  MatrixBase<T> :: getColDimension() const {
	return _dimCol;
}


template <typename T>
bool MatrixBase<T> :: matchExactDimesions(const MatrixBase<T> &mb) const{
	return (this->_dimFi==mb._dimFi) && (this->_dimCol==mb._dimCol);
}

template <typename T>
bool MatrixBase<T> :: matchMultDimesions(const MatrixBase<T> &mb)  const{
	return this->_dimCol == mb._dimFi;
}

template <typename T>
MatrixBase<T> MatrixBase<T> :: deleteFi(uInt fiElim) const {
	if(fiElim==0 || fiElim>_dimFi || this->_dimFi==1)
		throw MatrixException((char*)"NO se puede realizar la eliminacion de la fila");
	
	fiElim--;	//Recordar que los arreglos son [0,...n-1], nosotros pasamos [1,...,n]
	
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
MatrixBase<T> MatrixBase<T> :: deleteCol(uInt colElim) const {
	if(colElim==0 || colElim>_dimCol || _dimCol==1)
		throw MatrixException((char*)"NO se puede realizar la eliminacion de la columna");
		
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
MatrixBase<T> MatrixBase<T> :: deleteFiCol(uInt i, uInt j) const {
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

template <typename T>	//genera aliasing
MatrixBase<T>& MatrixBase<T> :: swapFi(uInt i, uInt i2){
	if(i==0 || i>_dimFi || i2==0 || i2>_dimFi)
		throw MatrixException((char*)"Swap filas con posiciones no existentes");	
		
	if(i==i2)	//pequeña optimizacion
		return *this;
	
	T swapElem;
	
	for(int h=0;h<_dimCol;h++){
		swapElem = _matrix[i2-1][h];
		_matrix[i2-1][h] = _matrix[i-1][h];
		_matrix[i-1][h] = swapElem;	
	}
	
	return *this;
}

template <typename T>	//genera aliasing
MatrixBase<T>& MatrixBase<T> :: swapCol(uInt j, uInt j2){
	if(j==0 || j>_dimCol || j2==0 || j2>_dimCol)
		throw MatrixException((char*)"Swap columnas con posiciones no existentes");	

	if(j==j2)
		return *this;
	
	T swapElem;

	for(int h=0;h<_dimFi;h++){
		swapElem = _matrix[h][j2-1];
		_matrix[h][j2-1] = _matrix[h][j-1];
		_matrix[h][j-1] = swapElem;
	}

	return *this;
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
void MatrixBase<T> :: multiplyFiCol(int fiI, int colJ, const MatrixBase<T>& A, const MatrixBase<T>& B){
	for(int i=0; i<A._dimCol; i++){
		this->_matrix[fiI][colJ] = this->_matrix[fiI][colJ] + (A._matrix[fiI][i] * B._matrix[i][colJ]);
	}
}

#endif
