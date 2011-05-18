OBJS =  ../../code/matrix_exceptions.cpp ../../code/warp_cannon.cpp ../../code/linear_system.cpp
OBJSo = ../../code/matrix_exceptions.o ../../code/warp_cannon.o ../../code/linear_system.o

all: inv_vs_lu ajuste_epsilon

inv_vs_lu: inv_vs_lu.cpp $(OBJSo) ../../code/*.h
	g++ -o inv_vs_lu inv_vs_lu.cpp $(OBJSo)

ajuste_epsilon: ajuste_epsilon.cpp $(OBJSo) ../../code/*.h
	g++ -o ajuste_epsilon ajuste_epsilon.cpp $(OBJSo)
	
%.o: %.cpp
	g++ -c $<
	
clean:
	rm -f inv_vs_lu
	rm -f ajuste_epsilon
	rm -f *.o
