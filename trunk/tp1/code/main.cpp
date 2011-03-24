#include <cmath>

#define big_mathLib float

using namespace std;


int main(int argc, char** argv){
	int t;
	
	if (argc>1){
		t = argv[1];
	} 
	else 
	{
		t = 10;			/*elegir dsp valor por defecto*/
	}
	
	big_mathLib pi = Gregory(t);
	

	return 0;
}
