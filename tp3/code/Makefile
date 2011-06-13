OBJS = parametrization.cpp spline.cpp curve.cpp polynomial.cpp spline_tester.cpp
OBJSo = parametrization.o spline.o curve.o polynomial.o spline_tester.o
MATH = -lm
CFLAGS = -ggdb 

all: tp3 test

tp3: main.cpp $(OBJSo)
	g++ -o tp3 $(CFLAGS) $(MATH) main.cpp $(OBJSo)
	
test: test.cpp $(OBJSo)
	g++ -o test $(CFLAGS) $(MATH) test.cpp $(OBJSo)	
	
%.o: %.cpp
	g++ -c $< $(MATH)
	
clean:
	rm -f tp3
	rm -f test
	rm -f *.o
