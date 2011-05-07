#ifndef __WARP_CANNON_H__
#define __WARP_CANNON_H__

#include "includes.h"
#include "vector.h"
#include "matrix.h"

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

#endif

