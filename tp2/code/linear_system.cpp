#include "linear_system.h"

linearSystem::linearSystem(const Matrix<double> A, const Vector<double> d): _A(A), _d(d){
	_dim = _A.getFiDimension();
}
linearSystem::~linearSystem(){}

Vector<double> linearSystem::usingInverse(){
	Matrix<double> A_inverse(_A.inverse());
	Vector<double> x(_dim);
	x = (A_inverse*_d.traspuesta()).traspuesta();
	return x;
}

Vector<double> linearSystem::usingLU(){
	Matrix<double> lu(_A.LU());
	cout << "LU" << lu;
	linearSystem ls(lu,_d);										//LUx=d
	Vector<double> z(ls.forwardSub());							//Ux=z
	ls._d=z;
	Vector<double> x(ls.backSub());								//Ux=z
	return x;
}

Vector<double> linearSystem::backSub(){
	
}

Vector<double> linearSystem::forwardSub(){
	
}
