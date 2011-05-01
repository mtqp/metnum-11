#include "includes.h"

#include "matrix_base.h"		//se supone q dsp nadie la va a ver a esta clase
#include "matrix_exceptions.h"
//#include "saving_data.h"		//no esta completo.

#include "vector.h"
#include "matrix_c.h"

int** initMatrix(int,int);

int main(int argc, char** argv){
	try
	{
		cout << "No se esta haciendo NINGUN FREE!!!!!!" << endl;
		
		if(argc < 2){
			cout << "Te olvidaste de mandar los parámetros capo!" << endl;
			return 0;
		}

		int dim = atoi(argv[1]);
		Matrix<int> A(dim,dim);
		for(int i=1;i<=dim;i++){
			for(int j=1;j<=i;j++){
				if(i==j) A.setValue(2,i,j);
				else A.setValue(0,i,j);
			}
		}
		A.setValue(5,3,2);
		A.print();
		cout << endl;
		cout << A.maxUnderDiag(2) << endl;
		
/*			
		int dim = atoi(argv[1]);
		Vector<int> x(dim);
		for(int i=1;i<=dim;i++){
			x.setValue(i,i);
		}
		
		cout << "X CON DIMENSION = " << x.dimension() << "	pointer=" << (int) &x << endl;
		cout << x;
		cout << "X traspuesta();" << endl;
		cout << x.traspuesta();
		cout << "X^TRASPUESTA pointer=" << (int) &x << endl;
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
		

		MatrixBase<int> A(matrix,dimFi,dimCol);
		//MatrixBase<int> B(mUno,dimCol,dimFi);		
		MatrixBase<int> B(mUno,dimCol,1);
		cout << "--> A" << endl;
		cout << A;
		cout << "A traspuesta" << endl;
		cout << A.traspuesta();
		A.setValue(300,1,1);
		cout << A;
//		A + A * A;
		
/*		cout << "swap fi 2 4" << endl;
		cout << A.swapFi(2,4);
		cout << "swap col 3 1" << endl;
		cout << A.swapCol(3,1) << endl;

/*		cout << "A -C3" << endl;
		cout << A.deleteCol(3);
/*		cout << "A -F2" << endl;
		cout << A.deleteFi(2);
/*		cout << "A -F2 -C3" << endl;
		cout << A.deleteFiCol(2,3);
		
	
		cout << "-------------------" << endl;
		cout << "--> B" << endl;
		cout << B;
		cout << "-------------------" << endl;
		cout << "--> A+B" << endl;
		cout << A+B;
		cout << "-------------------" << endl;
/*		cout << "--> A*B" << endl;
		cout << A*B;
		cout << "-------------------" << endl;
		cout << "--> B*3" << endl;
		cout << B*3;
	*/	
		//cout << "det A = " << A.det() << endl;
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
