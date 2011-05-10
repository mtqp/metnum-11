#include "warp_cannon.h"

WarpCannon :: WarpCannon(warpData wd, uInt dim) : _position(dim), _A(dim), _d(dim){
	if((wd.position).dimension() != dim) throw MatrixException((char*)"No se puede construir WarpCannon por inconsistencia en las dimensiones de los datos y lo que se pretende crear");
	_dim = dim;
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
	Vector<double> attack_point;
	Matrix<double> attack_A;
	attackData ad(_dim);

	if (setStrategy() == attack){
		//atacar
		attack_point(getAimPosition());
		attack_A(getMatrixAttack(attack_point));
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
*/
Matrix<double> WarpCannon :: getMatrixAttack(Vector<double> attack_point){
	/* Quiero A tal que A*_position=attack_point 	*
	 * Tengo _dim ecuaciones y _dim*_dim incognitas por lo que dim*dim-dim coeficientes de A estan libres*/
	
	/* Empiezo con una matriz mal condicionada */
	Matrix<double> attack_A(_dim,BadK);
	
	/* Seteo una columna (elegida tal que en esa posicion el vector _position sea distinto de cero) con los valores tal que al multiplicarla por _position de attack_point */
	uInt col = 1;
	bool zero = _position.getValue(col)==0;
	for(int i=2; i<=_dim && zero; i++){
		col = i;
		zero = _position.getValue(col)==0;
	}
	if(!zero){
		double acum;
		double value;
		for(int i=1; i<=_dim; i++){
			acum = 0;
			for(int j=1; j<=_dim; j++){
				if(j!=col){
					acum += attack_A.getValue(i,j)*_position.getValue(j);
				}
			}
			value = attack_point.getValue(i);
			value -= acum;
			value /= _position.getValue(col);
			attack_A.setValue(value,i,col);
		}
	}
	
	return attack_A;
}
