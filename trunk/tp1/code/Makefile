OBJS =  big_mathLib.cpp
MATH = -lm
CFLAGS = -Wall

tpUno: main.cpp 
	g++ -o tp1 $(MATH) main.cpp 

%.o: %.c
	g++ -c $< $(MATH)

clean:
	rm -f tp1
	rm -f *.o
