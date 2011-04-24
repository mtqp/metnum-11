#include "matrix_exceptions.h"

MatrixException :: MatrixException(char* exception){
	message = exception;
}

MatrixException :: ~MatrixException(){}

void MatrixException :: show(){
	cout << "MatrixException: " << message << endl;
}

