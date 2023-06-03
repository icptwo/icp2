// CH10:countchar.c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NUM_CHAR 26
int main(int argc, char * argv[])
{
  if (argc < 3) { return EXIT_FAILURE; } // need input and output
  char charcount[NUM_CHAR] = {0}; // initialize all elements to zeros
  // open the input file
  FILE * infptr;
  infptr = fopen(argv[1], "r");
  if (infptr == NULL) { return EXIT_FAILURE; }
  // count the occurrences of the characters
  int onechar;
  do
    {
      onechar = fgetc(infptr);
      if (isupper(onechar)) { charcount[onechar - 'A'] ++; }
      if (islower(onechar)) { charcount[onechar - 'a'] ++; }
    }  while (onechar != EOF);
  fclose (infptr);   // close the input file
  FILE * outfptr;
  outfptr = fopen(argv[2], "w");   // open the output file
  if (outfptr == NULL)  { return EXIT_FAILURE; }
  int ind;
  for (ind = 0; ind < NUM_CHAR; ind ++)
    { fprintf(outfptr, "%c: %d\n", ind  + 'A', charcount[ind]); }
  fclose (outfptr);   // close outupt file
  return EXIT_SUCCESS;
}
