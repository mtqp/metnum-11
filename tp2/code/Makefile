OBJS =  matrix_exceptions.cpp
OBJSo =  matrix_exceptions.o
MATH = -lm
CFLAGS = -ggdb 

all: test tp2

tp2: main.cpp 
	g++ -o tp2 $(CFLAGS) $(MATH) main.cpp $(OBJSo) 

test: test.cpp $(OBJSo) *.h 
	g++ -o test $(CFLAGS) $(MATH) test.cpp $(OBJSo)
	
%.o: %.cpp
	g++ -c $< $(MATH)
	
clean:
	rm -f tp2
	rm -f test
	rm -f *.o
