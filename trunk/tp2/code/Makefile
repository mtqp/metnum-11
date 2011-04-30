OBJS =  matrix_exceptions.cpp
OBJSo =  matrix_exceptions.o
MATH = -lm
CFLAGS = -ggdb 

all: matrix tp2

matrix: main.cpp $(OBJSo) 
	g++ -o matrix $(CFLAGS) $(MATH) main.cpp $(OBJSo) 

tp2: tp2.cpp
	g++ -o tp2 tp2.cpp
	
%.o: %.cpp
	g++ -c $< $(MATH)
	
clean:
	rm -f tp2
	rm -f matrix
	rm -f *.o
