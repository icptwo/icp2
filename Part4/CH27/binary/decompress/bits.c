// CH27:binary:decompress:bits.c
#include "bits.h"
int readBit(FILE * fptr, unsigned char * bit,
	    unsigned char * whichbit, unsigned char * curbyte)
{
  int ret = 1;
  if ((* whichbit) == 0)
    {
      // read a byte from the file
      ret = fread(curbyte, sizeof(unsigned char), 1, fptr);
    }
  if (ret != 1) { return -1; } // read fail
  // shift the bit to the correct location
  unsigned char temp = (* curbyte) >> (7 - (* whichbit));
  temp = temp & 0X01; // get only 1 bit, ignore the others
  // printf("readBit = %c\n", temp + '0');
  * whichbit = ((* whichbit) + 1) % 8;   // increase by 1 for the next bit
  * bit = temp;
  return 1;
}
int readByte(FILE * fptr, unsigned char * onebyte,
	     unsigned char * whichbit, unsigned char * curbyte)
{
  int iter;
  unsigned char byte = 0;
  unsigned char bit;
  for (iter = 0; iter < 8; iter ++)
    {
      if (readBit(fptr, & bit, whichbit, curbyte) == -1) { return -1; }
      byte <<= 1;
      byte = byte | bit;
    }
  * onebyte = byte;
  return 1;
}
int removePad(FILE * fptr, unsigned char * whichbit,
	      unsigned char * curbyte)
{
  int rtv;
  unsigned char bit;
  while ((* whichbit) != 0)
    {
      rtv = readBit(fptr, & bit, whichbit, curbyte);
      if (rtv == -1) { return -1; }
    }
  return rtv;
}
