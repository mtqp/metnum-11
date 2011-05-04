#include "includes.h"
#include "matrix.h"
#include "vector.h"
#include "matrix_exceptions.h"

int main(int argc, char** argv){
	try
	{
		/*Matrix<int>A(1,1);
		Matrix<int>B(A);*/
		
		/*
			AQUI VA EL PROGRAMA!
		*/
		Matrix<double> A(2);
		A.setValue(3,1,1);
		A.setValue(2,2,1);
		A.setValue(1,1,2);
		A.setValue(2,2,2);

		cout << "A" << endl;
		cout << A << endl;

		Matrix<double> B(2);		
		B=A.inverse();
		
		Matrix<double> C(2);
		C=A*B;
		
		cout << "C" << endl;
		cout << C << endl;
		
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

