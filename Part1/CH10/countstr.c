// CH10:countstr.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 81
int main(int argc, char * argv[])
{
  if (argc < 4) { return EXIT_FAILURE; } // input word output
  FILE * infptr;
  infptr = fopen(argv[1], "r");   // open the input file
  if (infptr == NULL) { return EXIT_FAILURE; }
  FILE * outfptr;
  outfptr = fopen(argv[2], "w");   // open the output file
  if (outfptr == NULL)
    {
      fclose (infptr);
      return EXIT_FAILURE;
    }
  int count = 0;
  char oneline[LINE_LENGTH];
  while (fgets(oneline, LINE_LENGTH, infptr) != NULL)
    {
      if (strstr(oneline, argv[3]) != NULL)
	{ fprintf(outfptr, "%s", oneline); }
      char * chptr = oneline;
      while (chptr != NULL)
	{
	  chptr = strstr(chptr, argv[3]);
	  if (chptr != NULL)
	    {
	      count ++;  
	      chptr ++;  // if "eyeye" counts as two "eye"
	      // if "eyeye" counts as one "eye", use 
	      // chptr += strlen(argv[3]);  
	    }
	}
    }
  fprintf(outfptr, "%d\n", count);
  fclose (infptr);   // close the input file
  fclose (outfptr);  // close outupt file
  return EXIT_SUCCESS;
}
