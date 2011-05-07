#ifndef __STRUCTS_H__
#define __STRUCTS_H__

#include "includes.h"

struct warpData {
	Matrix<double> A;
	Vector<double> d;
	Vector<double> position;
	Vector<double> previous_d[];		//poner tuplas!!!!
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

#endif
