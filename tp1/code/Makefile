OBJS =  printFuncs.cpp intFuncs.cpp decimalFuncs.cpp Real.cpp algorithms.cpp
OBJSo =  printFuncs.o intFuncs.o decimalFuncs.o Real.o algorithms.o
ASMOBJS = watchDoubles.o
MATH = -lm
CFLAGS = -ggdb 
NASM = -f elf
DEBUGNASM = -g

errores: main.cpp $(OBJSo) 
	g++ -o pi $(CFLAGS) $(MATH) main.cpp $(OBJSo) 

asm:
	nasm $(DEBUGNASM) $(NASM) watchDoubles.asm
	gcc -o asmErr $(CFLAGS) main.c $(ASMOBJS)

%.o: %.cpp
	g++ -c $< $(MATH)
	
%.o : %.asm
	nasm $(DEBUGNASM) $(NASM) $< 

clean:
	rm -f pi
	rm -f *.o
