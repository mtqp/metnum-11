#include "curve.h"

extern double pointDist(double x1, double y1, double x2, double y2);

Curve :: Curve(uint n, vector<pair> xy, Parametrization t){
	amount_control = n;
	vector<double> param = t.data();
	
	vector<double> x(n);
	vector<double> y(n);
	for(int i=0; i<n; i++){
		x[i] = xy[i].first;
		y[i] = xy[i].second;
	}
	
	S_x = new Spline(n,param,x);
	S_y = new Spline(n,param,y);
}

Curve :: Curve(uint n, vector<pair> xy, vector<double> t){
	amount_control = n;
	vector<double> param = t;
	
	vector<double> x(n);
	vector<double> y(n);
	for(int i=0; i<n; i++){
		x[i] = xy[i].first;
		y[i] = xy[i].second;
	}
	
	S_x = new Spline(n,param,x);
	S_y = new Spline(n,param,y);
}

Curve :: Curve(const Curve& c) : S_x(c.S_x), S_y(c.S_y)
{
	amount_control = c.amount_control;
}

Curve :: ~Curve(){
	delete S_x;
	delete S_y;
}

Curve Curve :: moveCurve(const pair fpoint, const pair ipoint) const{
	double t = this->nearPoint(ipoint);
	
	int position;
	if(isControlPoint(t,position)) return moveControlPoint(fpoint,position);
	
	return movePoint(fpoint,t);
	
}

pair Curve :: getNearPoint(const pair xy) const {
	double t = nearPoint(xy);
	//cout << "min_dis --> " << t << endl;
	pair near_point;
	near_point.first = S_x->evaluate(t);
	near_point.second= S_y->evaluate(t);
	return near_point;
}

bool Curve :: isControlPoint(double t, int& position) const{
	vector<double> params = S_x->getParams();
	int pos;
	bool isControl = false;
	for(pos=0; pos<params.size() && !isControl; pos++)
		isControl |= abs(params[pos]-t)<EPSILON;
	position = (isControl) ? pos-1 : -1;
	return isControl;
}

Curve Curve :: moveControlPoint(const pair fpoint, int position) const{
	vector<pair> paramX = S_x->getControls();
	vector<pair> paramY = S_y->getControls();
	vector<double> newParams(paramX.size());
	
	paramX[position].second = fpoint.first;
	paramY[position].second = fpoint.second;
	
	vector<pair> xy(paramX.size());
	for(int i=0; i<paramX.size(); i++){
		xy[i].first = paramX[i].second;
		xy[i].second = paramY[i].second;
		newParams[i] = paramX[i].first;
	}
	Curve movedCurve(xy.size(),xy,newParams);
	return movedCurve;
}

Curve Curve :: movePoint(const pair fpoint, double t) const
{
	vector<pair> paramsX = S_x->getControls();
	vector<pair> paramsY = S_y->getControls();
	vector<double> newParams(paramsX.size()+1);
	vector<pair> newControls(paramsX.size()+1);
	
	bool setNewPoint = false;
	int j=0;
	for(int i=0;i<newControls.size();i++){
		if(t>paramsX[j].first || setNewPoint){
			newParams[i] = paramsX[j].first;
			newControls[i].first = paramsX[j].second;
			newControls[i].second= paramsY[j].second;
			j++;
		}
		else
		{
			newParams[i] = t;
			newControls[i].first = fpoint.first;
			newControls[i].second= fpoint.second;
			setNewPoint = true;
		}
	}

	Curve movedCurve(newControls.size(),newControls,newParams);
	return movedCurve;
}
	
		
double Curve :: nearPoint(const pair xy) const{
	//cout << "Busco punto cercano a --> " << xy.first << " " << xy.second << endl;
	double min_dist = 0;							//empiezo con t igual al parametro correspondiente al primer pto de control, es arbitraria la eleccion
	double min_t;
	vector<double> critic_points;
	double dist1;
	double dist2;
	vector<double> param = S_x->getParams();
	for(int i=1; i<amount_control; i++){
		Polynomial pol = derivedDistancePolynom(i,xy,param[i-1]);
		//min_t = pol.zeros(param[i-1],param[i]);
		//cout << "pol entre pto de control extremo izq --> " << S_x->evaluate(param[i-1]) << " " <<  S_y->evaluate(param[i-1]) << endl;
		//cout << "pol entre pto de control extremo der --> " << S_x->evaluate(param[i]) << " " <<  S_y->evaluate(param[i]) << endl;
		critic_points = pol.zeros(param[i-1],param[i]);
		pol.print();
		//cout << "ceros del pol nro --> " << i << endl;
		//for(int j=0; j<critic_points.size(); j++)
			//cout << critic_points[j] << " --> ( " << S_x->evaluate(critic_points[j]) << " " << S_y->evaluate(critic_points[j]) << " ) --> " << evaluateDistance(xy,critic_points[j]) << endl;
		min_t = minInPoints(xy,critic_points);
		//cout << "min --> " << min_t << endl;
		dist1 = evaluateDistance(xy,min_dist);//S_x->evaluate(min_dist),S_y->evaluate(min_dist),xy.first,xy.second);
		dist2 = evaluateDistance(xy,min_t);//S_x->evaluate(min_t),S_y->evaluate(min_t),xy.first,xy.second);
		if(dist2<dist1) min_dist = min_t;
	}
	return min_dist;
}

vector<pair> Curve :: sampling(uint m) const{
	if(m<2) cout << "m debe ser mayor a 1 sino no se puede incluir a los extremos" << endl;
	vector<pair> sampling(m);
	double t_dist = 1.0/(m-1);
	double t = 0;
	for(int i=0; i<m; i++){
		sampling[i].first = S_x->evaluate(t);
		sampling[i].second = S_y->evaluate(t);
		t += t_dist;
	}
	return sampling;
}

double Curve :: minInPoints(const pair xy, vector<double> points) const {
	//cout << "En minInPoints" << endl;
	double globalMin = evaluateDistance(xy,points[0]);	//hay si o si uno por lo menos???
	double globalMinPoint = points[0];
	for(int i=1;i<points.size();i++){
		//cout << "global --> " << globalMin << endl;
		//cout << "point --> " << globalMinPoint << endl;
		if(globalMin > evaluateDistance(xy,points[i]))
		{
			globalMin = evaluateDistance(xy,points[i]);
			globalMinPoint = points[i];
		}
	}
	return globalMinPoint;
}

double Curve :: evaluateDistance(const pair xy, double point) const {
	return pointDist(S_x->evaluate(point), S_y->evaluate(point), xy.first, xy.second);
}

Polynomial Curve :: derivedDistancePolynom(int polIndex, const pair xy, double t) const{
	
	/******************************************************************************************************
	 *  Distancia al cuadrado entre el polinomio 'polIndex' en x y el polinomio 'polIndex' en y al punto xy 
	 * (S_x(t) - x)^2 + (S_y(t) - y)^2
	 * Como busco minimizar esta funcion, derivo -->
	 * 2*(S_x(t) - x)*(S_x(t) - x)' + 2*(S_y(t) - y)*(S_y(t) - y)'
	 * reacomodando los terminos queda la expresion -->
	 * E_x + E_y donde E_x -->
	 * (llamamos z=(t-tj))
	 * 2bx(ax-x) + 2(bx^2+2cx(ax-x))*z + 6(cxbx+dx(ax-x)))*z^2 + 4(2dxbx+cx^2)*z^3 + 10dxcx*z^4 + 6dx^2*z^5
	 * Idem para E_y
	 * *****************************************************************************************************/
	
	Polynomial pol_x = S_x->getPolynom(polIndex);
	Polynomial pol_y = S_y->getPolynom(polIndex);
	
	vector<double> coefs_x(pol_x.coefficients());
	vector<double> coefs_y(pol_y.coefficients());
	
	//calculo ax-x
	double cte_x = coefs_x[0] - xy.first;
	double cte_y = coefs_y[0] - xy.second;
	
	vector<double> newCoefs(6);				//queda un polinomio de grado 5
	newCoefs[0] = 2*(coefs_x[1]*cte_x + coefs_y[1]*cte_y);
	newCoefs[1] = 2*((pow(coefs_x[1],2.0)+2*coefs_x[2]*cte_x) + (pow(coefs_y[1],2.0)+2*coefs_y[2]*cte_y));
	newCoefs[2] = 6*((coefs_x[2]*coefs_x[1] + coefs_x[3]*cte_x) + (coefs_y[2]*coefs_y[1] + coefs_y[3]*cte_y));
	newCoefs[3] = 4*((2*coefs_x[3]*coefs_x[1] + pow(coefs_x[2],2.0)) + (2*coefs_y[3]*coefs_y[1] + pow(coefs_y[2],2.0)));
	newCoefs[4] = 10*((coefs_x[3]*coefs_x[2]) + (coefs_y[3]*coefs_y[2]));
	newCoefs[5] = 6*((pow(coefs_x[3],2.0)) + (pow(coefs_y[3],2.0)));
	
	Polynomial newPol(newCoefs,t,5);
	return newPol;
}

Curve& Curve :: operator= (const Curve &c)
{
	if(this!=&c){
		this->S_x = c.S_x;
		this->S_y = c.S_y;
		this->amount_control = c.amount_control;
	}
	return *this;
}

void Curve :: print() const{
	for(int i=1;i<amount_control;i++){
		cout << "S_x" << i << " = ";
		S_x->print(i);
	}
	for(int i=1;i<amount_control;i++){
		cout << "S_y" << i << " = ";
		S_y->print(i);
	}
}