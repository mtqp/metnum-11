OBJS =  ../../code/matrix_exceptions.cpp ../../code/warp_cannon.cpp ../../code/linear_system.cpp
OBJSo = ../../code/matrix_exceptions.o ../../code/warp_cannon.o ../../code/linear_system.o

all: inv_vs_lu
	
inv_vs_lu: inv_vs_lu.cpp $(OBJSo) ../../code/*.h
	g++ -o prueba_inv_vs_lu inv_vs_lu.cpp $(OBJSo)
	
%.o: %.cpp
	g++ -c $<
	
clean:
	rm -f inv_vs_lu
	rm -f *.o
