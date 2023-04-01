// CH27:binary:compress:occur.c
#include "occur.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define NUMCHAR 128 
int countOccur(char * filename, CharOccur * occur)
{
  FILE * fptr = fopen(filename, "r");
  int count = 0;
  if (fptr == NULL) { return 0; } // fopen fail
  // initialize the array elements
  int ind;
  for (ind = 0; ind < NUMCHAR; ind ++)
    {
      occur[ind].ascii = -1;
      occur[ind].occur = 0;
    }
  while (! feof (fptr))
    {
      int onechar = fgetc(fptr);
      if ((onechar != EOF) && (onechar < NUMCHAR))
	{
	  count ++;
	  occur[onechar].ascii = (char) onechar;
	  occur[onechar].occur ++;
	}
    }
  fclose (fptr);
  return count;
}
void printOccur(CharOccur * occur)
{
  int ind;
  for (ind = 0; ind < NUMCHAR; ind ++)
    {
      if (occur[ind].occur != 0)
	{ printf("%d %c %d\n", occur[ind].ascii, occur[ind].ascii,
		 occur[ind].occur); }
    }
}
static int compareOccur(const void * p1, const void * p2)
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
void sortOccur(CharOccur * occur)
{
  qsort(occur, NUMCHAR, sizeof(CharOccur), compareOccur);
}

#ifdef TEST_OCCUR
int main(int argc, char * * argv)
{
  if (argc != 2) { return EXIT_FAILURE; } // need a file name
  CharOccur chararr[NUMCHAR];
  int total = countOccur(argv[1], chararr);
  if (total != 0)
    {
      // printOccur(chararr);
      sortOccur(chararr);
      // printf("\n------------Sorted-----------\n");
      printOccur(chararr);
    }
  return EXIT_SUCCESS;
}
#endif
