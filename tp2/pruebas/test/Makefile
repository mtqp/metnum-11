OBJS =  ../../code/matrix_exceptions.cpp ../../code/warp_cannon.cpp ../../code/linear_system.cpp
OBJSo = ../../code/matrix_exceptions.o ../../code/warp_cannon.o ../../code/linear_system.o

all: inv_vs_lu inv_vs_lu_promedio prom_vs_direct ajuste_epsilon

inv_vs_lu: inv_vs_lu.cpp $(OBJSo) ../../code/*.h
	g++ -o inv_vs_lu inv_vs_lu.cpp $(OBJSo)

inv_vs_lu_promedio: inv_vs_lu_promedio.cpp $(OBJSo) ../../code/*.h
	g++ -o inv_vs_lu_promedio inv_vs_lu_promedio.cpp $(OBJSo)

prom_vs_direct: prom_vs_direct.cpp $(OBJSo) ../../code/*.h
	g++ -o prom_vs_direct prom_vs_direct.cpp $(OBJSo)

ajuste_epsilon: ajuste_epsilon.cpp $(OBJSo) ../../code/*.h
	g++ -o ajuste_epsilon ajuste_epsilon.cpp $(OBJSo)
	
%.o: %.cpp
	g++ -c $<
	
clean:
	rm -f inv_vs_lu
	rm -f inv_vs_lu_promedio
	rm -f prom_vs_direct
	rm -f ajuste_epsilon
	rm -f *.o
