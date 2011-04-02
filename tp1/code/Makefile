OBJS =  printFuncs.cpp intFuncs.cpp Real.cpp
ASMOBJS = watchDoubles.o
MATH = -lm
CFLAGS = -ggdb -Wall
NASM = -f elf
DEBUGNASM = -g

errores: main.cpp 
	g++ -o errores $(MATH) main.cpp $(OBJS) 

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
