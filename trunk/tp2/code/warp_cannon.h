#ifndef __WARP_CANNON_H__
#define __WARP_CANNON_H__

#include "includes.h"

struct warpData {
	Matrix<double> A;
	Vector<double> d;
	Vector<double> position;
	Vector<double> previous_d[];
	uInt  turn; 
	double threshold; 
	bool  failedAttack;	
};

struct attackData{
	Matrix<double> A;
	Vector<double> d;
};

enum Strategy{
	attack,
	disguise,
	fail
};

class WarpCannon{
	public:
		WarpCannon(warpData wp);
		~WarpCannon();
	
		attackData attack();	//genera matrix mal condicionada y multiplicar x vector

	private:
		Strategy setStrategy();
		Vector<double> getAimPosition();
		Matrix<double> getMatrixAttack();
		Matrix<double> getBadKMatrix();
	
		Matrix<double> _A;
		Vector<double> _d;
		Vector<double> _position;
		Vector<double> _previous_d[];
		uInt  	_turn; 
		double  _threshold; 	
		bool    _faiedAttack;
};

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

#endif

