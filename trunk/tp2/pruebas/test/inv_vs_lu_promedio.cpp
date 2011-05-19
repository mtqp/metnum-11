#include "../../code/includes.h"
#include "../../code/structs.h"
#include "../../code/matrix.h"
#include "../../code/vector.h"
#include "../../code/warp_cannon.h"
#include "../../code/linear_system.h"

/* argv[1] --> hasta que dimension de matriz se quiere testear 
 * argv[2] --> cuantos test por cada dimension, para promediar */

int main(int argc, char** argv){
	srand(time(NULL));
	cout.precision(20);
	cout.setf(ios::scientific,ios::floatfield);

	uInt dim;
	uInt tests = atoi(argv[2]);
	for(uInt i=2; i<=atoi(argv[1]); i++){
		double err_inv = 0;
		double err_lu = 0;
		dim = i;
		for(uInt k=0; k<tests; k++){
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
				inv.setValue(abs(inv.getValue(j) - pos.getValue(j)),j);
				err_inv += inv.normDos();
				lu.setValue(abs(lu.getValue(j) - pos.getValue(j)),j);
				err_lu += lu.normDos();
			}
		}
		
		err_inv /= tests;
		err_lu /= tests;
		cout << i << " " << err_inv << " " << err_lu << endl;	
	}
	
	return 0;
}