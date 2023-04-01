// CH27:binary:decompress:bits.h
#ifndef BITS_H
#define BITS_H
#include <stdio.h>
// read one bit from a file
int readBit(FILE * fptr, unsigned char * bit,
	    unsigned char * whichbit, unsigned char * curbyte);
// read one byte
int readByte(FILE * fptr, unsigned char * onebyte,
	     unsigned char * whichbit, unsigned char * curbyte);
int removePad(FILE * fptr, unsigned char * whichbit, unsigned char * curbyte);
#endif
