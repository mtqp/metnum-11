OBJS =  printFuncs.cpp intFuncs.cpp decimalFuncs.cpp Real.cpp algorithms.cpp
ASMOBJS = watchDoubles.o
MATH = -lm
CFLAGS = -ggdb 
NASM = -f elf
DEBUGNASM = -g

errores: main.cpp $(OBJS)
	g++ -o errores $(CFLAGS) $(MATH) main.cpp $(OBJS) 

asm:
	nasm $(DEBUGNASM) $(NASM) watchDoubles.asm
	gcc -o asmErr $(CFLAGS) main.c $(ASMOBJS)

%.o: %.cpp
	g++ -c $< $(MATH)
	
%.o : %.asm
	nasm $(DEBUGNASM) $(NASM) $< 

clean:
	rm -f errores
	rm -f *.o
