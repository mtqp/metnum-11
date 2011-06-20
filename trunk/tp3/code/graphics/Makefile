OBJS = ../polynomial.o ../parametrization.o ../spline.o ../curve.o ../functions.o
MATH = -lm
CFLAGS = -ggdb 

all: generador

generador: curve_generator.cpp $(OBJS)
	g++ -o curve_generator $(CFLAGS) $(MATH) curve_generator.cpp $(OBJS)
		
%.o: %.cpp %.h
	g++ -c $< $(MATH)
	
clean:
	rm -f tp3
	rm -f test
	rm -f *.o
