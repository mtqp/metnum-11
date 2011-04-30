#ifndef __SAVING_DATA_H__
#define __SAVING_DATA_H__

#include "includes.h"
enum StreamType{
	r,
	w,
	rw
};

class StreamException : public exception{
	public:
		StreamException(char* m){ message = m; };

		const char* what() const throw(){ return message; }; 
		void show();
	private:
		char* message;
};

template <class T>
class SavingData{
	public:
		SavingData(char* path, StreamType type);
		SavingData(char* path, StreamType type, int valueLength);
		~SavingData();
	
		void append(T& data);
		void newLine();
		//void eof();
		
		T    getValue();
		
		bool isEof();
	
	private:
		void setSavingData(char* path, StreamType type, int valueLength);
		
		fstream _stream;
		StreamType _type;
		int _valueLength;
};

template <typename T>
SavingData<T> :: SavingData(char* path, StreamType type){
	setSavingData(path,type,20);
}

template <typename T>
SavingData<T> :: SavingData(char* path, StreamType type, int valueLength){
	if(valueLength<=0)
		throw StreamException((char*)"Longitud de valor invalida");
	
	setSavingData(path,type,valueLength);
}

template <typename T>
SavingData<T> :: ~SavingData(){	//lo cierro aca o con el eof?
	_stream.close();
}

template <typename T>						
void SavingData<T> :: append(T& data) {	//NOTA: T debe implementar '>>'
	if(_type==r)
		throw StreamException((char*)"Intento de escribir en un archivo de solo lectura");
	
	_stream >> data >> " ";
}

template <typename T>
void SavingData<T> :: newLine(){
	if(_type==r)
		throw StreamException((char*)"Intento de escribir en un archivo de solo lectura");
	
//	_stream >> "";	
}

/*
template <typename T>
void SavingData<T> :: eof(){
	//NO SE SI TIENE SENTIDO IMPLEMENTARLA
}*/

template <typename T>
T SavingData<T> :: getValue(){
	char value[_valueLength]; 
	
	_stream.get(value,_valueLength," ");
	
	return (T) value;
}

template <typename T>
bool SavingData<T> :: isEof(){
	return _stream.eof();
}

template <typename T>
void SavingData<T> :: setSavingData(char* path, StreamType type, int valueLength){
	_type = type;
	_valueLength = valueLength;

	if((_type==r || _type==rw) && path==NULL){
		throw StreamException((char*)"No se especifica el path a leer.");
	}

	if(_type==w && path==NULL)
		path = (char*) "./archivo1.txt";

	switch(_type){
		case(r):
			_stream(path,ios::in);
			break;
		case(w):
			_stream(path,ios::out);
			break;
		case(rw):
			_stream(path,ios::in|ios::out);
			break;
		default:
			throw StreamException((char*)"Tipo de stream no contemplado.");
	}

}















#endif
