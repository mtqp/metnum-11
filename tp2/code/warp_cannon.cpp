#include "warp_cannon.h"

WarpCannon :: WarpCannon(warpData wd, uInt dim) : _position(dim), _A(dim), _d(dim){
	if((wd.position).dimension() != dim) throw MatrixException((char*)"No se puede construir WarpCannon por inconsistencia en las dimensiones de los datos y lo que se pretende crear");
	
	_turn = wd.turn;
	_position = wd.position;
	_threshold = wd.threshold;
	_failedAttack = wd.failedAttack;
	
	/* Si es el primer turno quedan con ceros */
	_A = wd.A;
	_d = wd.d;
	//_previous_d = previous_d;
}

WarpCannon :: ~WarpCannon(){}
/*
attackData WarpCannon :: attack(){
	Vector<double> d;
	Matrix<double> A;
	attackData ad;

	if (setStrategy() == attack){
		//atacar
		d(getAimPosition());
		A(getMatrixAttack());
	}
	else
	{
		if(setStrategy() == disguise){
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
	
	return ad; //hay q devolver la struct!!!!
}*/


Strategy WarpCannon :: setStrategy(){
	if(_failedAttack)
		return fail;

	double condition_number = _A.K();
	if(_turn==8 || condition_number<=_threshold)
		return attack;
		
	return disguise;
}
 
/*
Vector<double> WarpCannon :: getAimPosition(){}

Matrix<double> WarpCannon :: getMatrixAttack(){}

Matrix<double> WarpCannon :: getBadKMatrix()
*/
