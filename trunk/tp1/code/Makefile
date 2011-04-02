OBJS =  printFuncs.cpp intFuncs.cpp Real.cpp
MATH = -lm
CFLAGS = -Wall

errores: main.cpp 
	g++ -o errores $(MATH) main.cpp $(OBJS)

%.o: %.cpp
	g++ -c $< $(MATH)

clean:
	rm -f errores
	rm -f *.o
