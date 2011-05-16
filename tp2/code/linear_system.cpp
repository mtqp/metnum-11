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
	linearSystem ls(lu,_d);									//LUx=d
	Vector<double> z(ls.forwardSub());						//Ux=z
	ls._d=z;
	Vector<double> x(ls.backSub());							//Ux=z
	return x;
}

Vector<double> linearSystem::backSub(){
	Vector<double> res(_d.dimension());
	double acum;
	for(int i=_dim;i>=1;i--){
		acum = 0;
		for(int j=_dim;j>i;j--){
			acum+=(_A.getValue(i,j)*res.getValue(j));
		}
		res.setValue((_d.getValue(i)-acum)/_A.getValue(i,i),i);
	}
	return res;
	cout << res;
}

Vector<double> linearSystem::forwardSub(){
	Vector<double> res(_d.dimension());
	double acum;
	for(int i=1;i<=_dim;i++){
		acum = 0;
		for(int j=1;j<i;j++){
			acum+=(_A.getValue(i,j)*res.getValue(j));
		}
		res.setValue((_d.getValue(i)-acum),i);							//la diagonal de L esta toda en uno por eso no divido
	}
	return res;
}
