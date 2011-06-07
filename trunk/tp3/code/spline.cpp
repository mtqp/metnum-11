#include "spline.h"

Spline :: Spline(int n, float* x){
	float h[n-1];		//se interpreta desde cero (h_0, h_1, ... , h_n-1)
	float alpha[n-2];	//se interpreta desde uno (alpha_1, alpha_2, ... , alpha_n-1)
	for(int i=0; i<n-1;i++){
		h[i]=x[i+1]-x[i];
		if(i!=0)
			alpha[i] = (3/h[i])*(a[i+1]-a[i])-(3/h[i-1])*(a[i]-a[i-1]);
	}
}

Spline :: ~Spline(){}