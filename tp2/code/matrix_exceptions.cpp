#include "matrix_exceptions.h"

MatrixException :: MatrixException(char* exception){
	message = exception;
}

const char* MatrixException :: what() const throw(){
	return message;
}
