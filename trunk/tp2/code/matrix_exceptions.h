#ifndef __MATRIX_EXCEPTIONS_H__
#define __MATRIX_EXCEPTIONS_H__

#include "includes.h"

class MatrixException{
	public:
		MatrixException(char*);
		~MatrixException();

		void show();
	private:
		char* message;
};

#endif
