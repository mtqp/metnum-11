OBJS =  matrix_exceptions.cpp
OBJSo =  matrix_exceptions.o
MATH = -lm
CFLAGS = -ggdb 

pi: main.cpp $(OBJSo) 
	g++ -o matrix $(CFLAGS) $(MATH) main.cpp $(OBJSo) 

%.o: %.cpp
	g++ -c $< $(MATH)
	
clean:
	rm -f matrix
	rm -f *.o
