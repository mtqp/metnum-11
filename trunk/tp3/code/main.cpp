#include "spline.h"

int main(int argc, char** argv){

	uint n = 4;
	
	double x[n];
	x[0] = 1;
	x[1] = 2;
	x[2] = 4;
	x[3] = 5;
	
	double f_x[n];
	f_x[0] = 2;
	f_x[1] = 1;
	f_x[2] = 4;
	f_x[3] = 3;
		
	Spline S(n,x,f_x);
	S.print(1);
	
	return 0;
}
