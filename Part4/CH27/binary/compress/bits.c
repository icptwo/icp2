// CH27:binary:compress:bits.c
#include "bits.h"
// * whichbit indicates which bit this is written to
// (0 means leftmost, 7 means rightmost) curbyte is the current byte
// When * whichbit is zero, curbyte is reset
// When * whichbit is 7, this byte is written to the file
// The function returns 1 if a byte is written to the file
// returns 0 if no byte is written, -1 if write and fails
int writeBit(FILE * fptr, unsigned char bit, 
	     unsigned char * whichbit, unsigned char * curbyte)
{
  if ((* whichbit) == 0) { * curbyte = 0; } // reset the byte
  // shift the bit to the correct location
  unsigned char temp = bit << (7 - (* whichbit));
  * curbyte |= temp; // store the data
  int value = 0;
  if ((* whichbit) == 7)
    {
      int ret;
      ret = fwrite(curbyte, sizeof(unsigned char), 1, fptr);
      // printByte(* curbyte); // for debugging
      if (ret == 1) { value = 1; }
      else { value = -1; }
    }
  * whichbit = ((* whichbit) + 1) % 8;
  return value;
}
int writeByte(FILE * fptr, unsigned char onebyte,
	      unsigned char * whichbit, unsigned char * curbyte)
{
  int iter;
  for (iter = 0; iter < 8; iter ++)
    {
      unsigned char bit = ((onebyte & 0X80) != 0);
      if (writeBit(fptr, bit, whichbit, curbyte) == -1) { return -1; }
      onebyte <<= 1;
    }
  return 1;
}
int padZero(FILE * fptr, unsigned char * whichbit, unsigned char * curbyte)
{
  int rtv;
  while ((* whichbit) != 0)
    {
      rtv = writeBit(fptr, 0, whichbit, curbyte);
      if (rtv == -1) { return -1; }
    }
  return rtv;
}

