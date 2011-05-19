#include "../../code/includes.h"
#include "../../code/structs.h"
#include "../../code/matrix.h"
#include "../../code/vector.h"
#include "../../code/warp_cannon.h"
#include "../../code/linear_system.h"

extern const double EPSILON_ERROR;

/* argv[1] --> dimension de matriz se quiere testear 
 * argv[2] --> cantidad de turnos a ejecutar */

Matrix<double> getMatrixAttack(uInt _dim, const Vector<double> _position,const Vector<double> attack_point);

int main(int argc, char** argv){
	srand(time(NULL));
	cout.precision(20);
	cout.setf(ios::scientific,ios::floatfield);

	uInt dim = atoi(argv[1]);
	uInt turns = atoi(argv[2]);
	double err_prom;
	double err;
	
	/* Posicion que intenta descubrir sin usar promedio */
	Vector<double> my_position(dim);
	my_position.createRandomVector();
	
	/* Matriz mal condicionada */
	Matrix<double> my_bad_cond(dim,BadK);
	
	/* Ataque primer turno */
	Vector<double> my_attack(dim);
	my_attack = (my_bad_cond*my_position.traspuesta()).traspuesta();
	
	pair<Vector<double>*,double>* history_enemy_position;
	history_enemy_position = new pair<Vector<double>*,double> [turns-1];
	pair<Vector<double>*,double>* history_my_position;
	history_my_position = new pair<Vector<double>*,double> [turns-1];
	for(uInt k=0; k<turns-1; k++){
		history_enemy_position[k].first = new Vector<double>(dim);
		history_my_position[k].first = new Vector<double>(dim);
	}

	/* Posicion que intenta descubrir usando promedio */
	Vector<double> enemy_position(dim);
	enemy_position.createRandomVector();
	
	/* Matriz mal condicionada */
	Matrix<double> enemy_bad_cond(dim,BadK);
	
	/* Ataque primer turno */
	Vector<double> enemy_attack(dim);
	enemy_attack = (enemy_bad_cond*enemy_position.traspuesta()).traspuesta();
	
	for(uInt i=2; i<=turns; i++){
		
		/*************************************************************/
		/********************* Atacamos nosotros *********************/
		/*****************Usamos promedio de promedios****************/
		linearSystem ls(enemy_bad_cond,enemy_attack);
		
		/* Resulvo el sistema para encontrar al enemigo */
		Vector<double> lu(dim);
		lu = ls.usingLU();
		
		/* Guardo las posiciones calculadas para sacar promedio */
		*history_enemy_position[i-2].first = lu;
		
		/* Creo la estructura de ataque */
		warpData wd(dim);
		wd.turn = i;
		wd.position = my_position;
		wd.A = enemy_bad_cond;
		wd.d = enemy_attack;
		wd.position_enemy = history_enemy_position;
			
		/* Llamada a la funcion principal */
		WarpCannon wp(wd,dim);
		attackData wa(dim);
		wa = wp.attack();
		
		*history_enemy_position[i-2].first = wa.d;
		
		/*************************************************************/
		/********************* Ataca el enemigo **********************/
		/************************Usa promedio*************************/
		linearSystem e_ls(my_bad_cond,my_attack);
		
		/* Resulvo el sistema para encontrar al enemigo */
		Vector<double> e_lu(dim);
		e_lu = ls.usingLU();
		
		/* Guardo las posiciones calculadas para sacar promedio */
		*history_my_position[i-2].first = lu;
		
		/* Creo la estructura de ataque */
		warpData e_wd(dim);
		e_wd.turn = i;
		e_wd.position = enemy_position;
		e_wd.A = my_bad_cond;
		e_wd.d = my_attack;
		e_wd.position_enemy = history_my_position;
			
		/* Llamada a la funcion principal */
		WarpCannon e_wp(wd,dim);
		attackData e_wa(dim);
		e_wa = e_wp.attack();
		
		/* Acomodo las cosas para el siguiente turno */
		my_bad_cond = wa.A;
		my_attack = wa.d;
		
		enemy_bad_cond = e_wa.A;
		enemy_attack = e_wa.d;
				
		/* Saco la diferencia */
		Vector<double> my_dif(dim);
		Vector<double> enemy_dif(dim);
		for(uInt j=1; j<=dim; j++){
			my_dif.setValue(abs(wa.d.getValue(j) - enemy_position.getValue(j)),j);
			err_prom = my_dif.normDos();
			enemy_dif.setValue(abs(e_wa.d.getValue(j) - my_position.getValue(j)),j);
			err = enemy_dif.normDos();
		}
	
		cout << i << " " << err_prom << " " << err << endl;
	}
	
	return 0;
}

Matrix<double> getMatrixAttack(uInt _dim, const Vector<double> _position, const Vector<double> attack_point){
	/* Quiero A tal que A*_position=attack_point
	 * Tengo _dim ecuaciones y _dim*_dim incognitas por lo que dim*dim-dim coeficientes de A estan libres*/

	/* Empiezo con una matriz mal condicionada */
	Matrix<double> attack_A(_dim,BadK);
	
	/* Seteo una columna (elegida tal que en esa posicion el vector _position sea distinto de cero) con los valores tal que al multiplicarla por _position de attack_point */
	uInt col = 1;
	bool zero = abs(_position.getValue(col))<EPSILON_ERROR;
	for(uInt i=2; i<=_dim && zero; i++){
		col = i;
		zero = abs(_position.getValue(col))<EPSILON_ERROR;
	}
	if(!zero){
		double acum;
		double value;
		for(uInt i=1; i<=_dim; i++){
			acum = 0;
			for(uInt j=1; j<=_dim; j++){
				if(j!=col){
					acum += attack_A.getValue(i,j)*_position.getValue(j);
				}
			}
			value = attack_point.getValue(i);
			value -= acum;
			value /= _position.getValue(col);
			attack_A.setValue(value,i,col);
		}
	}

	return attack_A;
}