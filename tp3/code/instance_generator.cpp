#include "includes.h"

#define M_SMPS 500000

void createFile(char* filename, int control_count, int range);
vector<pair> getRandomControlPoints(int control_count,int range);
int compare_doubles(const void *a, const void* b);
double getRandDouble(int range);

int main(int argc, char** argv)
{
	srand(time(NULL));
	if(argc<5)
	{
		cout << "uso: ./instance_generator [file_name] [#files] [#control_count] [range]" << endl;
		return 0;
	}
	
	int archives_count = atoi(argv[2]);
	int control_count = atoi(argv[3]);
	int range = atoi(argv[4]);
	
	cout << "Cargando el archivo: ";
	for(int i=0;i<archives_count;i++)
	{
		//char file_i_name[100] = strcpy(argv[1]);		//no seas guacho y le pases argv[1] > 100 chars!
		//cout << "Cargando el archivo: " << file_i_name << endl;
		//createFile(strcat(file_i_name,itoa(i)),control_count,range);
		cout << ".";
		
		int controls = rand()%control_count;
		if(controls<=2)
			controls = control_count;
		createFile(argv[1],controls,range);
	}
	cout << endl << "Archivo cargado" << endl;

	ofstream out;
	out.open(argv[1],ios::app);
	out << -1  << endl;
	out.close();
	return 0;
}

//precond, se llamo a srand...!!!
void createFile(char* filename, int control_count, int range)
{
	ofstream out;
	out.open(filename,ios::app);
	if(!out.is_open())
	{
		cout << "No se pudo salvar el archivo " << filename << endl;
		return;
	}
	
	out << control_count << " " << M_SMPS << endl; //-->guardo #puntos_de_control y M
	
	vector<pair> control_points(control_count);
	control_points = getRandomControlPoints(control_count,range);
	
	for(int i=0;i<control_count;i++)
		out << control_points[i].first << " " << control_points[i].second << endl;
		
	out << endl << 0 << " " << 0 << endl;		//-->x*,y*
	out << endl << getRandDouble(range) << " " << getRandDouble(range) << endl;		//-->x**,y**

	out.close();
}

//precond, se llamo a srand...!!!
vector<pair> getRandomControlPoints(int control_count,int range)
{
	vector<pair> randControlPoints(control_count);
	double X[control_count];
	int sign = 1;
	for(int i=0;i<control_count;i++)
		X[i] = getRandDouble(range);
	
	qsort(&X,control_count,sizeof(double),compare_doubles);
	
	for(int i=0;i<control_count;i++){
		randControlPoints[i].first = X[i];
		randControlPoints[i].second= getRandDouble(range);
	}
	
	return randControlPoints;
}

//precond, se llamo a srand...!!!
double getRandDouble(int range)
{
	double maxRand = (double) RAND_MAX;
	int sign = (rand()%3!=0)? 1 : -1;
	return sign * (rand()/maxRand) * ((double)(range+1));
}


int compare_doubles(const void *a, const void* b)
{
	double* arg1 = (double*) a;
    double* arg2 = (double*) b;
    if( *arg1 < *arg2 ) return -1;
    else if( *arg1 == *arg2 ) return 0;
    else return 1;	
}

