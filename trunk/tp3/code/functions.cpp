#include <cmath>

double pointDist(double x1, double y1, double x2, double y2){
	double delta_x = x1 - x2;
	double delta_y = y1 - y2;
	
	delta_x *= delta_x;
	delta_y *= delta_y;
		
	return sqrt(delta_x + delta_y);
}