#!/usr/bin/python

from random import randint, seed, choice
import sys

def generar_input( nombre, instancias ):
	fIn = open(nombre,'w')
	for instancia in instancias:
		t_digits,cantIt= instancia
		fIn.write( "%d %d \n"%(t_digits,cantIt))
	fIn.write("-1 -1")
	fIn.close()	


def main():
	seed()
	cantIt=10
	t_digits=10
	
	print "Generando instancias con cantIt fijas..."
	instancias_cantIt = []
	for i in range (1,52):
		instancias_cantIt.append((i,cantIt))
	print "OK"
			
	print "Generando archivo con cantIt fijas..."
	generar_input( 'in/cantIt_%d.in'%(cantIt), instancias_cantIt )
	print "OK"
	
	print "Generando instancias con t_digits fijo..."
	instancias_t_digits = []
	hasta_iter=10
	for i in range (1,hasta_iter):
		instancias_t_digits.append((t_digits,i))
	print "OK"
			
	print "Generando archivo con t_digits fijo..."
	generar_input( 'in/t_digits_%d.in'%(t_digits), instancias_t_digits )
	print "OK"

if __name__=="__main__":
	main()
