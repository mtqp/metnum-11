#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "includes.h"

template <class T>
class Vector : public MatrixBase<T>{
	public:
		Vector(uInt dim);
		~Vector();
	
	
	private:
	
};

template <typename T>
Vector<T> :: Vector(){}


#endif
