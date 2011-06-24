#include "includes.h"

double getRandDouble(int range);

int main(int argc, char** argv){
	srand(time(NULL));
	if(argc<4)
	{
		cout << "uso: ./polynomial_generator [file_name] [#instance] [range]" << endl;
		return 0;
	}
	
	int amount_instance = atoi(argv[2]);
	double range = atoi(argv[3]);
	
	/* Abro el archivo para guardar los polinomios */
	ofstream out(argv[1]);
	if(!out.is_open()) 
	{
		cout << "No pudo crear el archivo para el polinomio" << endl;
		exit(-1);
	}

	out << amount_instance << endl;
	uint order = 5;
	for(int i=0; i<amount_instance; i++){
		cout << "Generando instancia nro: " << i << endl;
		
		/* Elijo e imprimo el xj */
		out << getRandDouble(range) << endl;
	
		/* Elijo e imprimo los coeficientes del polinomio */
		vector<double> pol(order+1);
		for(int j=0; j<=order; j++)
			out << getRandDouble(range) << " ";
		out << endl;
	}
		
	out.close();
	return 0;
}

//precond, se llamo a srand...!!!
double getRandDouble(int range)
{
	double maxRand = (double) RAND_MAX;
	int sign = (rand()%3!=0)? 1 : -1;
	return sign * (rand()/maxRand) * ((double)(range+1));
}