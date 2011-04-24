#include "includes.h"

#include "matrix_base.h"		//se supone q dsp nadie la va a ver a esta clase
#include "matrix_exceptions.h"

int** initMatrix(int,int);

int main(int argc, char** argv){
	try
	{
		int dimFi = atoi(argv[1]);
		int dimCol= atoi(argv[2]);
		
		//int matrix[dimFi][dimCol];
		int** matrix = initMatrix(dimFi,dimCol);
		
		int val = 1;
		for(int i=0; i<dimFi; i++)
			for(int j=0;j<dimCol; j++)
				matrix[i][j] = 1;
		
		//int** fuck=0;
		
		MatrixBase<int> mprueba(matrix,dimFi,dimCol);
		
//		cout << mprueba;
		
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
	int** res = (int**) malloc(sizeof(int**)* col);
	for(int j=0;j<col;j++){
		res[j] = (int*) malloc(sizeof(int*)*fi);
	}
	
	return res;
}
