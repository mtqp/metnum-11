OBJS = parametrization.o spline.o curve.o polynomial.o spline_tester.o functions.o
MATH = -lm
CFLAGS = -ggdb 

all: tp3 test generador

tp3: main.cpp $(OBJS)
	g++ -o tp3 $(CFLAGS) $(MATH) main.cpp $(OBJS)
	
test: test.cpp $(OBJS)
	g++ -o test $(CFLAGS) $(MATH) test.cpp $(OBJS)	

generador: instance_generator.cpp curve_generator.cpp $(OBJS)
	g++ -o instance_generator $(CFLAGS) $(MATH) instance_generator.cpp $(OBJS)
	g++ -o curve_generator $(CFLAGS) $(MATH) curve_generator.cpp $(OBJS)

%.o: %.cpp %.h
	g++ -c $< $(MATH)
	
clean:
	rm -f tp3
	rm -f test
	rm -f curve_generator
	rm -f *.o
