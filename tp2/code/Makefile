OBJS =  matrix_exceptions.cpp
OBJSo =  matrix_exceptions.o
MATH = -lm
CFLAGS = -ggdb 

all: matrix tp2

matrix: main.cpp $(OBJSo) *.h 
	g++ -o matrix $(CFLAGS) $(MATH) main.cpp $(OBJSo) 

tp2: tp2.cpp
	g++ -o tp2 $(CFLAGS) $(MATH) tp2.cpp $(OBJSo)
	
%.o: %.cpp
	g++ -c $< $(MATH)
	
clean:
	rm -f tp2
	rm -f matrix
	rm -f *.o
