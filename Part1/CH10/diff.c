// CH10:diff.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define LINELENGTH 81
int main(int argc, char * * argv)
{
  if (argc != 3) { return EXIT_FAILURE; }
  FILE * fptr1 = fopen(argv[1], "r");
  if (fptr1 == NULL) { return EXIT_FAILURE; }
  FILE * fptr2 = fopen(argv[2], "r");
  if (fptr2 == NULL)
    {
      fclose (fptr1);
      return EXIT_FAILURE;
    }
  char line1[LINELENGTH];
  char line2[LINELENGTH];
  while ((! feof(fptr1)) || (! feof(fptr2)))
    {
      char * rtv1;
      char * rtv2;
      rtv1 = fgets(line1, LINELENGTH, fptr1);
      rtv2 = fgets(line2, LINELENGTH, fptr2);
      if ((rtv1 != NULL) && (rtv2 != NULL))
	{
	  if (strcmp(line1, line2) != 0) 
	    {
	      printf("file1: %s", line1);
	      printf("file2: %s", line2);
	    }
	  // ignore when the two lines are the same
	}
      if ((rtv1 == NULL) && (rtv2 == NULL))
	{
	  // end of both files, do nothing
	}
      if ((rtv1 == NULL) && (rtv2 != NULL))
	{
	  // file 1 ends, file 2 not end
	  printf("file2: %s", line2);
	}
      if ((rtv1 != NULL) && (rtv2 == NULL))
	{
	  // file 2 ends, file 1 not end
	  printf("file1: %s", line1);
	}      
    }
  fclose (fptr1);
  fclose (fptr2);
  return EXIT_SUCCESS;
}
