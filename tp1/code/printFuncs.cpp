#include "printFuncs.h"

void printDouble(double decker){
    char * desmond = (char *) & decker;
    int i;
	cout << "double representation --> " << decker << endl;
	printNotacion();
	
	unsigned char* bits = (unsigned char*) malloc(sizeof(unsigned char)*8);

    for (i=sizeof(double)-1; i>=0; i--) {
         //printf ("%02X ", desmond[i]);
         printCharsetInBits(desmond[i], bits);
         printf ("%s ", bits);
    }
    printf ("\n");
}


void printCharsetInBits(char set, unsigned char* bits){
	unsigned char pot  = 128;
	unsigned char data = (unsigned char) set;
	
    for(int i=0; i<8; ++i)
    {
        if((data/pot)%2){
        	bits[i] = '1';
        }
        else {
        	bits[i] = '0';
        }
        
        pot /= 2;
    }
}

void printNotacion(){
	cout << "Notacion:" << endl;
	cout << "	izq = + significativa" << endl;
	cout << "	der = - significativa" << endl;
}


