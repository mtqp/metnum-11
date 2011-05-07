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
		
		Matrix<double> A(3);
		A.setValue(2,1,1);
		A.setValue(-2,1,2);
		A.setValue(1,1,3);
		A.setValue(-1,2,1);
		A.setValue(1,2,2);
		A.setValue(1,2,3);
		A.setValue(-1,3,1);
		A.setValue(3,3,2);
		A.setValue(5,3,3);
		
		cout << "A" << endl;
		cout << A << endl;
			
		Matrix<double> B(3);
		B=A.inverse();
		
		cout << "Inversa de A" << endl;
		cout << B << endl;
		
		Matrix<double> C(3);
		C=A*B;
		
		cout << "Id?" << endl;
		cout << C << endl;
		
		/*
		Matrix<double> C(2);
		C.setValue(4,1,1);
		C.setValue(4,1,2);
		C.setValue(0,2,1);
		C.setValue(5,2,2);

		
		cout << "C" << endl;
		cout << C << endl;
		cout << C.det() << endl;*/

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

