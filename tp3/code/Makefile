OBJS =  spline.cpp
OBJSo =  spline.o
MATH = -lm
CFLAGS = -ggdb 

all: tp3

tp3: main.cpp $(OBJSo)
	g++ -o tp3 $(CFLAGS) $(MATH) main.cpp $(OBJSo) 
	
%.o: %.cpp
	g++ -c $< $(MATH)
	
clean:
	rm -f tp3
	rm -f *.o
