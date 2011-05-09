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
	Matrix<double> attack_A(getBadKMatrix());
	
	/* Seteo una columna (elegida tal que en esa posicion el vector _position sea distinto de cero) con los valores tal que al multiplicarla por _position de attack_point */
	uInt col = 1;
	bool zero = _position.getValue(col)==0;
	for(int i=2; i<=_dim && zero; i++){
		col = i;
		zero = _position.getValue(col)==0;
	}

	if(!zero){
		uInt acum = 0;
		double value = 0;
		for(int i=1; i<=_dim; i++){
			for(int j=1; j<=_dim; j++){
				if(j!=col){
					acum += attack_A.getValue(i,j)*_position.getValue(j);
				}
			}
			value = attack_point.getValue(col) - acum;
			value /= _position.getValue(col);
			attack_A.setValue(value,i,col);
		}
	}
	
	return attack_A;
}

int asd = 0;
Matrix<double> WarpCannon :: getBadKMatrix() {
	Matrix<double> res(_dim);
	if(rand()%2){
		//matrix de hilbert por un coef
		double randomCoef = rand()%10;//ajustar ese modulo

		Matrix<double> bad_conditioned(_dim, BadK);
	
		res = randomCoef * bad_conditioned;	
	}
	else 
	{
		//matriz con casi filas ld
		double epsilon = 1.0/1000.0;
	
		Vector<double> randomV(createRandomVector());
	
		for(int i=1;i<=_dim;i++)
			for(int j=1;j<=_dim;j++){
				res.setValue(/*seed+j*/randomV.getValue(j),i,j);
				if(i==j){
					res.setValue(/*seed+j*/randomV.getValue(j)+epsilon,i,j);	
				}
			}
	}
	return res;
}

Vector<double> WarpCannon :: createRandomVector(){
	Vector<double> randV(_dim);
	
	double den;
	for(int i=1;i<=_dim;i++){
	//	den = (rand()%2*_dim)+1; //EL MODULO DE ESTO Q ES!?!?!?
		randV.setValue((rand()%_dim)/*/den*/,i);
	}
	
	return randV;
}

