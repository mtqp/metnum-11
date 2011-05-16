#ifndef __LINEAR_SYSTEM_H__
#define __LINEAR_SYSTEM_H__

#include "includes.h"
#include "vector.h"
#include "matrix.h"

class linearSystem{
	public:
		linearSystem(const Matrix<double> A, const Vector<double> d);
		~linearSystem();
		
		Vector<double> usingInverse();
		Vector<double> usingLU();

	private:
		Vector<double> backSub();
		Vector<double> forwardSub();
	
		uInt _dim;
		Matrix<double> _A;
		Vector<double> _d;
};

#endif

