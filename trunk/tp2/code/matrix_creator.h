#ifndef __MATRIX_CREATOR_H__
#define __MATRIX_CREATOR_H__

#include "includes.h"
#include "matrix_exceptions.h"

/*
	ESTA CLASE SOLO TIENE SENTIDO PARA POCOS TIPOS, CREO QUE INT ES EL UNICO para identidad, 
*/

template <class T>
class MatrixCreator : public MatrixBase<T> {
	public:
		MatrixCreator(MatrixType mt, int dimFi, int dimCol);
		//MatrixCreator(MatrixType[] mt); //ESTARIA BUENO PODER IMPLEMENTAR VARIAS FUNCIONALIDADES JUNTAS
		~MatrixCreator();
	
	protected:
	
	private:		
		
	
	
};

#endif
