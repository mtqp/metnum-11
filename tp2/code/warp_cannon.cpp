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
	//_previous_y = previous_y;
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
*/
int asd = 0;
Matrix<double> WarpCannon :: getBadKMatrix() {
	Matrix<double> res(_d.dimension());
	if(rand()%2){
		//matrix de hilbert por un coef
		double randomCoef = rand()%10;//ajustar ese modulo

		Matrix<double> bad_conditioned(_d.dimension(), BadK);
	
		res = randomCoef * bad_conditioned;	
	}
	else 
	{
		//matriz con casi filas ld
		double epsilon = 1.0/1000.0;
	
		Vector<double> randomV(createRandomVector());
	
		for(int i=1;i<=_d.dimension();i++)
			for(int j=1;j<=_d.dimension();j++){
				res.setValue(/*seed+j*/randomV.getValue(j),i,j);
				if(i==j){
					res.setValue(/*seed+j*/randomV.getValue(j)+epsilon,i,j);	
				}
			}
	}
	return res;
}

Vector<double> WarpCannon :: createRandomVector(){
	uInt dim = _d.dimension();

	Vector<double> randV(dim);
	
	double den;
	for(int i=1;i<=dim;i++){
	//	den = (rand()%2*dim)+1; //EL MODULO DE ESTO Q ES!?!?!?
		randV.setValue((rand()%dim)/*/den*/,i);
	}
	
	return randV;
}

