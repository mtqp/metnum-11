#ifndef __MATRIX_EXCEPTIONS_H__
#define __MATRIX_EXCEPTIONS_H__

#include "includes.h"

class MatrixException : public exception{
	public:
		MatrixException(char*);

		const char* what() const throw(); 
		void show();
	private:
		char* message;
};

#endif
