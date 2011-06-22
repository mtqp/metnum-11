#include "setp_polynomial.h"

double min(Setp_Polynomial pol, vector<double> points);

int main(int argc, char** argv){
	
	if(argc<3)
	{
		cout << "uso: ./set_params [input] [output]" << endl;
		return 0;
	}
	
	/* Abro los archivos */
	ifstream in(argv[1]);
	if(!in.is_open()) cout << "No se pudo abrir el archivo: " << argv[1] << endl;
	
	ofstream out(argv[2]);
	if(!out.is_open()) cout << "No se pudo abrir el archivo: " << argv[2] << endl;
	
	uint amount_instance;
	in >> amount_instance;
	cout << "Son " << amount_instance << " instancias" << endl;
	
	uint order = 5;
	for(int j=0; j<amount_instance; j++){
		cout << "Procesando instancia nro: " << j+1 << endl;
		/* Leo el orden del primer polinomio */
		uint xj;
		in >> xj;
	
		/* Leo los coeficientes de X */
		vector<double> coefs(order+1);
		for(int i=0; i<order+1; i++)
			in >> coefs[i];

		for(ull iter=10; iter<=10000000; iter*=10){
			cout << "Con iter = " << iter << endl;
			Setp_Polynomial pol(coefs,xj,order);
			
			vector<double> zeros(order);
			zeros = pol.zeros(0,1,0,iter);
			double min_zero = min(pol, zeros);
			
			out << iter << " " << pol.getAmountOp() << " " << pol.evaluate(min_zero) << endl; 
		}
	}
	
	in.close();
	out.close();
	
	return 0;
}

double min(Setp_Polynomial pol, vector<double> zeros){
	double min = zeros[0];
	for(int i=1; i<zeros.size(); i++)
		if(pol.evaluate(min)>pol.evaluate(zeros[i])) min=zeros[i];
	return min;
}