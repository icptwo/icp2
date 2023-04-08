// CH10:fscanf.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * * argv)
{
  if (argc != 2) { return EXIT_FAILURE; }
  FILE * fptr = fopen(argv[1], "r");
  if (fptr == NULL) { return EXIT_FAILURE; }
  int ind;
  // call fgetc five times
  for (ind = 0; ind < 5; ind ++)  { int ch = fgetc(fptr); }
  printf("ftell = %ld\n", ftell(fptr));
  fseek(fptr, 0, SEEK_SET); // return to the beginning of the file
  // call fscanf %d five times
  for (ind = 0; ind < 5; ind ++)
    {
      int val;
      if (fscanf(fptr, "%d", & val) == 1)
	{
	  // printf("val = %d\n", val);
	}
    }
  printf("ftell = %ld\n", ftell(fptr));
  fseek(fptr, 0, SEEK_SET); // return to the beginning of the file
  // call fscanf %d five times
  for (ind = 0; ind < 5; ind ++)
    {
      double val;
      if (fscanf(fptr, "%lf", & val) == 1)
	{
	  // printf("val = %lf\n", val);
	}
    }
  printf("ftell = %ld\n", ftell(fptr));
  fclose (fptr);
  return EXIT_SUCCESS;
}

