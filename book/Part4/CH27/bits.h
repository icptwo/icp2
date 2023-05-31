// CH27:bits.h
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
int padZero(FILE * fptr, unsigned char * whichbit,
	    unsigned char * curbyte);
// remove bits in the current byte in order to reach the next byte
int removePad(FILE * fptr, unsigned char * whichbit,
	      unsigned char * curbyte);
// read one bit from a file
int readBit(FILE * fptr, unsigned char * bit,
	    unsigned char * whichbit, unsigned char * curbyte);
// read one byte
int readByte(FILE * fptr, unsigned char * onebyte,
	     unsigned char * whichbit, unsigned char * curbyte);
#endif
