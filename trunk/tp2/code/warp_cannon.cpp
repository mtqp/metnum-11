#include "warp_cannon.h"

WarpCannon :: WarpCannon(warpData wd){
	/*_A = new Matrix<double>(wd.A);
	_d = new Vector<double>(wd.d);
	BLAH
	_position = */
}

WarpCannon :: ~WarpCannon(){

}

attackData WarpCannon :: attack(){
	Vector<double> d;
	Matrix<double> A;

	if (setStrategy() == attack)
	{
		//atacar
		d(getAimPosition());
		A(getMatrixAttack());
	}
	else
	{
		if(setStrategy() == disguise)
		{
			//despistar
			A(getBadKMatrix());
			d(A*_position);
			
		}
		else
		{
			//fallamos en el ataque, nueva estrategia
			//POR AHORA NO LE DAMOS PELOTA A ESTO.
		}
	}
	
	return NULL; //hay q devolver la struct!!!!
}


Strategy WarpCannon :: setStrategy(){

}

Vector<double> WarpCannon :: getAimPosition(){}

Matrix<double> WarpCannon :: getMatrixAttack(){}

Matrix<double> WarpCannon :: getBadKMatrix()

