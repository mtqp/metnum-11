#include "includes.h"

#include "matrix_base.h"		//se supone q dsp nadie la va a ver a esta clase
#include "matrix_exceptions.h"

int** initMatrix(int,int);

int main(int argc, char** argv){
	try
	{
		cout << "No se esta haciendo NINGUN FREE!!!!!!" << endl;
		
		if(argc < 3){
			cout << "Te olvidaste de mandar los parámetros capo!" << endl;
			return 0;
		}
			
	
		int dimFi = atoi(argv[1]);
		int dimCol= atoi(argv[2]);
		
		//int matrix[dimFi][dimCol];
		int** matrix = initMatrix(dimFi,dimCol);
		int** mUno   = initMatrix(dimCol,dimFi);
		int val = 0;
		for(int i=0; i<dimFi; i++)
			for(int j=0;j<dimCol; j++){
				val++;
				matrix[i][j] = val;
			//	mUno[i][j] = 2;
			}
		
		val = 10;
		for(int i=0; i<dimCol; i++)
			for(int j=0;j<dimFi; j++){
				val++;
				mUno[i][j] = val;
			}
		

		MatrixBase<int> A(matrix,dimFi,dimCol);
		MatrixBase<int> B(mUno,dimCol,dimFi);		
		cout << "--> A" << endl;
		cout << A;
		cout << "-------------------" << endl;
		cout << "--> B" << endl;
		cout << B;
/*		cout << "-------------------" << endl;
		cout << "--> A+B" << endl;
		cout << A+B;
		cout << "-------------------" << endl;
*/		cout << "--> A*B" << endl;
		cout << A*B;
/*		cout << "-------------------" << endl;
		cout << "--> B*3" << endl;
		cout << B*3;
	*/	
		
		/*
			AQUI VA EL PROGRAMA!
		*/
	}
	catch (MatrixException& e)
	{
		e.show();
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
