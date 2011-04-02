#ifndef __REAL_H__
#define	__REAL_H__

#define bestInt unsigned long long

class Real {
	public:
		Real();
		Real(bestInt valor);
		Real(bestInt valor, int t_digitos,bool trunca);
		~Real();
		
		Real operator+ (Real a); //--> van a ser constantes o no? PENSAR
		Real operator* (Real a);
		Real operator- (Real a);
		Real operator/ (Real a);
		Real operator= (const Real a);
		Real operator= (const bestInt a);
		Real raizCuad();
	
	private:
		double convertir();
		bool _trunca;
		char _tdigitos;
		char _real[8];
	
};

#endif
