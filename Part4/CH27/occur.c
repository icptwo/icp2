// CH27:occur.c
#include "occur.h"
#include <stdlib.h>
#include <strings.h>
int countOccur(char * filename, CharOccur * occur, int length)
{
  FILE * fptr = fopen(filename, "r");
  int count = 0;
  if (fptr == NULL) { return 0; } // fopen fail
  // initialize the array elements
  int ind;
  for (ind = 0; ind < length; ind ++)
    {
      occur[ind].ascii = -1;
      occur[ind].occur = 0;
    }
  while (! feof (fptr))
    {
      int onechar = fgetc(fptr);
      if ((onechar >= 0) && (onechar < length))
	{
	  count ++;
	  occur[onechar].ascii = (char) onechar;
	  occur[onechar].occur ++;
	}
    }
  fclose (fptr);
  return count;
}
void printOccur(CharOccur * occur, int length, FILE * fptr)
{
  int ind;
  for (ind = 0; ind < length; ind ++)
    {
      if (occur[ind].occur != 0)
	{
	  fprintf(fptr, "%d: %c %d\n", occur[ind].occur,
		  occur[ind].ascii, occur[ind].ascii);
	}
    }
}
int compareOccur(const void * p1, const void * p2)
{
  const CharOccur * ip1 = (const CharOccur *) p1;
  const CharOccur * ip2 = (const CharOccur *) p2;
  const int iv1 = ip1 -> occur;
  const int iv2 = ip2 -> occur;
  if (iv1 != iv2)
    { return (iv1 - iv2); }
  // same occurrences, ordered by the ASCII values
  const char cv1 = ip1 -> ascii;
  const char cv2 = ip2 -> ascii;
  return (cv1 - cv2);
}
