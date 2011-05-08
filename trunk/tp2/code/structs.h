#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include <utility>
#include "includes.h"
#include "matrix.h"
#include "vector.h"

struct warpData {
	uInt  turn;
	Vector<double> position;
	double threshold;
	bool failedAttack;
	
	/* Si es el primer turno quedan con ceros */
	Matrix<double> A;
	Vector<double> d;
	warpData(uInt dim) : A(dim), d(dim), position(dim){}
	pair<Vector<double>,double> previous_d[];
};

struct attackData{
	Matrix<double> A;
	Vector<double> d;
	attackData(uInt dim) : A(dim), d(dim){}
};

enum Strategy{
	attack,
	disguise,
	fail
};

#endif
