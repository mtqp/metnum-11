#include "../curve.h"

vector<pair> getSamples(uint smp_count, uint amount_control, vector<pair> xy, ParamType parametrization);
void saveCurve(char* argv, char* paramType, vector<pair> smp);
int compare_doubles(const void *a, const void* b);

int main(int argc, char** argv){
	
	if(argc<4){
		cout << "uso: [entrada] [salidaPolinomio] [salidaCurva]" << endl;
		exit(0);
	}
	
	cout << "Los coeficientes del polinomio se pasan de la forma:" << endl;
	cout << "\t--> a0 + a1.(x-xj) + a2.(x-xj)^2 + ... + an.(x-xj)^n" << endl;
	
	/***************************** Entrada ****************************/
	/* Abro el archivo */
	ifstream in(argv[1]);
	if(!in.is_open()) cout << "No se pudo abrir el archivo: " << argv[1] << endl;
	
	/* Leo el orden del primer polinomio */
	uint orderX;
	in >> orderX;
	
	/* Leo los coeficientes de X */
	vector<double> coefs_x(orderX+1);
	for(int i=0; i<orderX+1; i++)
		in >> coefs_x[i];
	
	
	/* Ignoro la linea en blanco */
	//in.ignore(0,'\n');
	
	/* Leo el orden del primer polinomio */
	uint orderY;
	in >> orderY;
	
	/* Leo los coeficientes de Y */
	vector<double> coefs_y(orderY+1);
	for(int i=0; i<orderY+1; i++)
		in >> coefs_y[i];
	
	// Leo la cantidad de puntos de control 
	uint amount_count;
	in >> amount_count;
	
	// Leo la cantidad de samples que desea hacerse
	uint smp_count;
	in >> smp_count;
	
	in.close();
	
	/**************************** Programa ****************************/
	//Creo ambos polinomios que formaran (Px(t),Py(t));
	Polynomial Px(coefs_x,orderX);
	Polynomial Py(coefs_y,orderY);
	
//	Px.print();
//	Py.print();
	
	double sampling_interval = 6.28/smp_count;
	
	srand(time(NULL));
	double control_t[amount_count];
	for(int i=0;i<amount_count;i++)	{	//genero amount_count t's en el [0,...,1]
		control_t[i] = (double) rand()/RAND_MAX;
	}
		
	//ordeno los t para generar los puntos de control de la curva
	qsort(&control_t,amount_count,sizeof(double),compare_doubles);
	
	vector<pair> xy(amount_count);
	for(int i=0;i<amount_count;i++)
	{
			xy[i].first = Px.evaluate(control_t[i]);
			xy[i].second= Py.evaluate(control_t[i]);
	}
	// Creo la parametrizaciones y curvas
	// Obtengo el muestreo de las splines originales
	vector<pair> sampling_uni 	  = getSamples(smp_count, amount_count, xy, Uniform);
	vector<pair> sampling_clength = getSamples(smp_count, amount_count, xy, Chord_length);
	vector<pair> sampling_cent    = getSamples(smp_count, amount_count, xy, Centripetal);
	
	/************************* Salida Polinomio ***********************/
	char file_pol[strlen(argv[2])];
	strcpy(file_pol,argv[2]);
	ofstream out_p(strcat(file_pol,".dat"));
	if(!out_p.is_open()) 
	{
		exit(-1);
	}
	
	double t_eval = -3.14;
	for(int i=0;i<smp_count;i++)
	{
		out_p << Px.evaluate(t_eval) << " " << Py.evaluate(t_eval) << endl;
		t_eval += sampling_interval;
	}
	
	out_p.close();
	
	/************************* Salida Curva ***************************/
	saveCurve(argv[3], "Uniform.dat", sampling_uni);
	saveCurve(argv[3], "ChordLength.dat", sampling_clength);
	saveCurve(argv[3], "Centripetal.dat", sampling_cent);
		
	return 0;
}

vector<pair> getSamples(uint smp_count, uint amount_control, vector<pair> xy, ParamType parametrization)
{
	Parametrization param(amount_control,xy,parametrization);	
	Curve curve(amount_control,xy,param);
	return curve.sampling(smp_count);
}

void saveCurve(char* argv, char* paramType, vector<pair> smp)
{
	char file_name[strlen(argv)];
	strcpy(file_name, argv);
	ofstream out(strcat(file_name,paramType));
	if(!out.is_open())
	{
		cout << "No se pudo salva la curva con parametrizacion: " << paramType << endl;
		return;
	}
	for(int i=0;i<smp.size();i++)
		out << smp[i].first << " " << smp[i].second << endl;
}

int compare_doubles(const void *a, const void* b)
{
	double* arg1 = (double*) a;
    double* arg2 = (double*) b;
    if( *arg1 < *arg2 ) return -1;
    else if( *arg1 == *arg2 ) return 0;
    else return 1;	
}
