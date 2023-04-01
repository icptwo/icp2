// CH27:binary:compression:bits.h
#ifndef BITS_H
#define BITS_H
#include <stdio.h>
// write one bit to a file
int writeBit(FILE * fptr, unsigned char bit, 
	     unsigned char * whichbit, unsigned char * curbyte);
// save one byte
int writeByte(FILE * fptr, unsigned char onebyte,
	      unsigned char * whichbit, unsigned char * curbyte);
// fill unused bits in a byte to 0 and write the byte to the file
int padZero(FILE * fptr, unsigned char * whichbit, unsigned char * curbyte);
#endif
