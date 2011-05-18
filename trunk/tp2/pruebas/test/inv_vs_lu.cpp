#include "../../code/includes.h"
#include "../../code/structs.h"
#include "../../code/matrix.h"
#include "../../code/vector.h"
#include "../../code/warp_cannon.h"
#include "../../code/linear_system.h"

int main(int argc, char** argv){
	srand(time(NULL));
	cout.precision(20);
	cout.setf(ios::scientific,ios::floatfield);

	uInt dim;
	double err_inv;
	double err_lu;
	for(uInt i=2; i<=atoi(argv[1]); i++){
		dim = i;
		
		/* Matriz mal condicionada */
		Matrix<double> bad_cond(dim,BadK);
		bool isInversible = bad_cond.isInversible(); 

		/* Posicion que intenta descubrir */
		Vector<double> pos(dim);
		pos.createRandomVector();
		
		/* Punto donde pretende disparar */
		Vector<double> d(dim);
		d = (bad_cond*pos.traspuesta()).traspuesta();
		isInversible = bad_cond.isInversible(); 
		
		linearSystem ls(bad_cond,d);
		
		Vector<double> inv(dim);
		inv = ls.usingInverse();
		
		Vector<double> lu(dim);
		lu = ls.usingLU();
		
		/*for(uInt j=1; j<=dim; j++){
			err_inv += abs(inv.getValue(j) - pos.getValue(j));
			err_lu += abs(lu.getValue(j) - pos.getValue(j));
		}
		
		cout << i << " " << err_inv << " " << err_lu << endl;*/

		for(uInt j=1; j<=dim; j++){
			inv.setValue(abs(inv.getValue(j) - pos.getValue(j)),j);
			err_inv = inv.normDos();
			lu.setValue(abs(lu.getValue(j) - pos.getValue(j)),j);
			err_lu = lu.normDos();
		}
		cout << i << " " << err_inv << " " << err_lu << endl;		
	}
	
	return 0;
}