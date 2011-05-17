OBJS =  matrix_exceptions.cpp warp_cannon.cpp linear_system.cpp
OBJSo =  matrix_exceptions.o warp_cannon.o linear_system.o
MATH = -lm
CFLAGS = -ggdb 

all: test tp2 prueba_error

tp2: main.cpp $(OBJSo)
	g++ -o tp2 $(CFLAGS) $(MATH) main.cpp $(OBJSo) 

test: test.cpp $(OBJSo) *.h
	g++ -o test $(CFLAGS) $(MATH) test.cpp $(OBJSo)
	
prueba_error: prueba_error.cpp $(OBJSo) *.h
	g++ -o prueba_error $(CFLAGS) $(MATH) prueba_error.cpp $(OBJSo)
	
%.o: %.cpp
	g++ -c $< $(MATH)
	
clean:
	rm -f tp2
	rm -f test
	rm -f *.o
