#include "includes.h"
#include "structs.h"
#include "matrix.h"
#include "vector.h"
#include "warp_cannon.h"
//#include "structs.h"
//#include "warp_cannon.h"


/*	arreglar lo q qdo feo del determinante
	constructor por copia de vector
	constructor y destructor q warpcannon
	generador de matrices mal condicionadas (matrix.h)
*/


int main(int argc, char** argv){
	try
	{
		Matrix<double> A(3);
		A.setValue(1,1,1);
		A.setValue(0,1,2);
		A.setValue(2,1,3);
		A.setValue(1,2,1);
		A.setValue(0,2,2);
		A.setValue(2,2,3);
		A.setValue(1,3,1);
		A.setValue(2,3,2);
		A.setValue(1,3,3);
		Matrix<double> B(3);
		cout << "A" << endl;
		cout << A << endl;
		B = A.gaussianElim(false);
		cout << B << endl;
/*		srand(time(NULL));
		cout.precision(6);
		/*Matrix<int>A(1,1);
		Matrix<int>B(A);
		
		int dim = 10;
		
		warpData wd(dim);
		wd.d.setValue(1,1);
		wd.d.setValue(2,2);
		wd.d.setValue(3,3);
		wd.d.setValue(4,4);		
		wd.position.setValue(10,1);
		wd.position.setValue(5,2);
		wd.position.setValue(5,3);
		wd.position.setValue(1,4);
	
		Matrix<double> C(dim,BadK);
		cout << C.K() << endl;
	
		WarpCannon wp(wd,dim);
		Matrix<double> B(wp.getMatrixAttack(wd.d));
		cout << "resultado: " << endl;
		cout << B.K() << endl;
*/		
/*		for(int i=0;i<20;i++)
			cout << wp.createRandomVector();
		cout << "mal condicionada hilberiana" << endl;
		//for(int i=0;i<2;i++){
		Matrix<double> A(wp.getBadKMatrix());
			cout << "isInversible? = " << A.isInversible() << endl;
			cout << "det value = "  << A.det() << endl;
			cout << "nro condicion = " << A.K() << endl;
			cout << A;
			cout << "inversa de A" << endl;
			cout << A.inverse();
			cout << "id???" << endl;
			cout << A * A.inverse();
			cout << "---------------------------" << endl;
			
		Matrix<double> B(wp.getBadKMatrix());
			cout << "isInversible? = " << B.isInversible() << endl;
			cout << "det value = "  << B.det() << endl;
			cout << "nro condicion = " << B.K() << endl;
			cout << B;
			cout << "inversa de B" << endl;
			cout << B.inverse();
			cout << "id???" << endl;
			cout << B * B.inverse();
			cout << "---------------------------" << endl;
		//}
	
/*		Vector<double> v(10);
		for(int i=1;i<=10;i++)
			v.setValue(i,i);
		
		cout << "v" << endl;
		cout << v;
		
/*		cout << "v tras" << endl;
		cout << v.traspuesta().traspuesta();
	*//*
		Vector<double> x(v.traspuesta());
		cout << x;
		
/*		Vector<double> z(10,true);
		z = v.traspuesta();
		cout << "freaking z" << endl;
		cout << z;
//		cout << v.traspuesta();	
/*		Vector<double> copy(v.traspuesta());
		cout << "v tras copy" << endl << copy;
		
/*		MatrixBase<double> A(3,3);
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
		cout << "det A"  << A.det() << endl;
/*			
		Matrix<double> B(3);
		B=A.inverse();
		
		cout << "Inversa de A" << endl;
		cout << B << endl;
		
		Matrix<double> C(3);
		C=A*B;
		
		cout << "Id?" << endl;
		cout << C << endl;
//*/		
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

