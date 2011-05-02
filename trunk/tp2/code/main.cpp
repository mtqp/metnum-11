#include "includes.h"

#include "matrix.h"
#include "vector.h"
#include "matrix_exceptions.h"

int main(int argc, char** argv){
	try
	{
		/*
			AQUI VA EL PROGRAMA!
		*/
	}
	catch (MatrixException& e) //HACER ANDAR BIEN!
	{
		cout << "MatrixException: " << e.what() << endl;
		/*
			Las excepciones se utilizan para no cortar con la ejecucion del programa,
			se puede hacer un manejo mas inteligente de ser necesario, basta con agregar
			funcionalidad al objeto MatrixException
		*/
	}

	return 0;
}

