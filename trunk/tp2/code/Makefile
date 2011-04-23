OBJS =  matrix_base.cpp
OBJSo =  matrix_base.o
MATH = -lm
CFLAGS = -ggdb 

pi: main.cpp $(OBJSo) 
	g++ -o matrix $(CFLAGS) $(MATH) main.cpp $(OBJSo) 

%.o: %.cpp
	g++ -c $< $(MATH)
	
clean:
	rm -f matrix
	rm -f *.o
