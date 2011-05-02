#ifndef __WARP_CANNON_H__
#define __WARP_CANNON_H__

#include "includes.h"

class WarpCannon{
	public:
		WarpCannon();
		~WarpCannon();
	
		//shoot();
	
	private:
		Matrix<double> _A;
		Vector<double> _mePos;
		Vector<double> _enemyPos;
		uInt		   _securityShoot;	//porcentaje entre 0...100 de viabilidad de disparar al target
};


#endif
