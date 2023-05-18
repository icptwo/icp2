// CH27:convert.c
// convert a test case from letter-occurrence pair to print the letters
// for example, if input is a 23, this program prints a 23 times
#include <stdio.h>
#include <stdlib.h>
#define NUMCHAR 256
int main(int argc, char * * argv)
{
  if (argc != 3) { return EXIT_FAILURE; }
  FILE * inptr = fopen(argv[1], "r");
  if (inptr == NULL) { return EXIT_FAILURE; }
  int occur[NUMCHAR] = {0};
  char val;
  int count;
  while (fscanf(inptr, "%c %d\n", & val, & count) == 2)
    {
      // printf("%c %d\n", val, count);
      if (occur[(int) val] != 0) { printf("Repeated character %c\n", val); }
      occur[(int) val] = count;
    }
  fclose(inptr);
  FILE * outptr = fopen(argv[2], "w");
  int ind;
  for (ind = 0; ind < NUMCHAR; ind ++)
    {
      for (count = 0; count < occur[ind]; count ++)
	{
	  fprintf(outptr, "%c", ind);
	}
    }
  fclose(outptr);
  return EXIT_SUCCESS;
}
