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
	double epsilon;
	for(uInt k=2; k<=atoi(argv[1]); k++){
		dim = k;
		epsilon = 1.0;
		
		/*Creo un vector random que va a ser las filas de la matriz */
		Vector<double> randomV(dim);
		randomV.createRandomVector();

		/* Armo la matriz con las filas igual al vector random */
		Matrix<double> random_ld(dim);
		for(uInt i=1;i<=dim;i++)
			for(uInt j=1;j<=dim;j++)
				random_ld.setValue(randomV.getValue(j),i,j);
		
		/* Hago variar el epsilon entre 1 y 1.0 × 10^-9 (10^10 no entra en uInt)*/ 
		for(uInt i=1; i<=1000000; i*=10){
			epsilon = 1.0/(double)i;
			
			/* Armo la matriz igual a random_ld sumando epsilon a la diagonal */
			Matrix<double> copy(random_ld);
			for(uInt j=1;j<=dim;j++)
				copy.setValue(random_ld.getValue(j,j)+epsilon,j,j);
				
			cout << k << " " << epsilon << " " << copy.K() << endl;
		}
	}
	
	return 0;
}