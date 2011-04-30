OBJS =  matrix_exceptions.cpp
OBJSo =  matrix_exceptions.o
MATH = -lm
CFLAGS = -ggdb 

tp2: tp2.cpp
	g++ -o tp2 tp2.cpp

matrix: main.cpp $(OBJSo) 
	g++ -o matrix $(CFLAGS) $(MATH) main.cpp $(OBJSo) 
	
%.o: %.cpp
	g++ -c $< $(MATH)
	
clean:
	rm -f tp2
	rm -f matrix
	rm -f *.o
