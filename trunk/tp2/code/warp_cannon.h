#ifndef __WARP_CANNON_H__
#define __WARP_CANNON_H__

#include "includes.h"
#include "structs.h"
#include "matrix.h"
#include "vector.h"

class WarpCannon{
	public:
		WarpCannon(warpData wd, uInt dim);
		~WarpCannon();
	
		attackData attack();	//genera matrix mal condicionada y multiplicar x vector

	private:
		//Strategy setStrategy();
		Vector<double> getAimPosition();
		Matrix<double> getMatrixAttack(Vector<double> attack_point);
	
		uInt _dim;
		uInt  _turn;
		Vector<double> _position;
		double _threshold;
		
		/* Si es el primer turno quedan con ceros */
		Matrix<double> _A;
		Vector<double> _d;
		pair<Vector<double>*,double>* _position_enemy;
};

#endif
