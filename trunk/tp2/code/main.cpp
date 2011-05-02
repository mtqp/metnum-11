#include "includes.h"

#include "matrix_base.h"		//se supone q dsp nadie la va a ver a esta clase
#include "matrix_exceptions.h"

#include "vector.h"
//#include "matrix_c.h"

int** initMatrix(int,int);

int main(int argc, char** argv){
	try
	{

		if(argc < 3){
			cout << "Te olvidaste de mandar los parámetros capo!" << endl;
			return 0;
		}


		int dimFi = atoi(argv[1]);
		int dimCol= atoi(argv[2]);
		
		MatrixBase<int> A(dimFi, dimCol);
		
		for(int i=1; i<=dimFi; i++)
			for(int j=1;j<=dimCol; j++){
				A.setValue(i+j, i, j);
			}
		
		int dim = atoi(argv[1]);
		Vector<int> x(dim);
		for(int i=1;i<=dim;i++){
			x.setValue(i,i);
		}
		
		cout << "A" << endl;
		cout << A;
/*		cout << "xtrasp" << endl;
		cout << x.traspuesta();
*/		
		cout << "x" << endl;
		cout << x;
		cout << "A * x " << endl;
		cout << x*A;
		
		Vector<int> y(dim);
		y = x*A;
		cout << "y" << endl;
		cout << y;
		
//		Vector<int> y(x);
/*		

		cout << "X CON DIMENSION = " << x.dimension() << "	pointer=" << (int) &x << endl;
		cout << x;
		cout << "X traspuesta();" << endl;
//		cout << x.traspuesta();
c

cout << "x!!!" << x;		cout << x.traspuesta();
		cout << "do we get here??" << endl;
//		x.getValue(1);
//		cout << "X^TRASPUESTA pointer=" << (int) &x << endl;
//		cout << "norma1=" << x.normaUno() << "\tnorma2=" << x.normaDos() << "\tnormaInf=" << x.normaInf() << endl;

/*	
		int dimFi = atoi(argv[1]);
		int dimCol= atoi(argv[2]);
		
		//int matrix[dimFi][dimCol];
		int** matrix = initMatrix(dimFi,dimCol);
		int** mUno   = initMatrix(dimCol,dimFi);
		int val = 1;
		for(int i=0; i<dimFi; i++)
			for(int j=0;j<dimCol; j++){
				val++;
				matrix[i][j] = val;
				//matrix[i][j] = 1;
			}
		
		val = 10;
		for(int i=0; i<dimCol; i++)
			for(int j=0;j<dimFi; j++){
				val++;
				mUno[i][j] = val;
			}
		

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

int** initMatrix(int fi,int col){
	int** res = (int**) malloc(sizeof(int**)* fi);
	for(int j=0;j<fi;j++){
		res[j] = (int*) malloc(sizeof(int*)*col);
	}
	return res;
}
