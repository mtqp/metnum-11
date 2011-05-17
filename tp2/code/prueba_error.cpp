#include "includes.h"
#include "structs.h"
#include "matrix.h"
#include "vector.h"
#include "warp_cannon.h"
#include "linear_system.h"

int main(int argc, char** argv){
	cout.precision(20);
	cout.setf(ios::scientific,ios::floatfield);

	uInt dim;
	double err_inv;
	double err_lu;
	for(uInt i=2; i<=atoi(argv[1]); i++){
		dim = i;
		
		/* Matriz mal condicionada */
		Matrix<double> bad_cond(dim,BadK);
		
		/* Posicion que intenta descubrir */
		Vector<double> pos(dim);
		pos.createRandomVector();
		
		/* Punto donde pretende disparar */
		Vector<double> d(dim);
		d = (bad_cond*pos.traspuesta()).traspuesta();
		
		linearSystem ls(bad_cond,d);
		
		Vector<double> inv(dim);
		inv = ls.usingInverse();
		
		Vector<double> lu(dim);
		lu = ls.usingLU();
		
		for(uInt j=1; j<=dim; j++){
			err_inv += abs(inv.getValue(j) - pos.getValue(j));
			err_lu += abs(lu.getValue(j) - pos.getValue(j));
		}
		
		cout << err_inv << " " << err_lu << endl;
	}
	
	return 0;
}
