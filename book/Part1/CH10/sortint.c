// CH10:sortint.c
#include <stdio.h>
#include <stdlib.h>
int comparefunc(const void * arg1, const void * arg2)
{
  const int * ptr1 = (const int *) arg1; // cast type
  const int * ptr2 = (const int *) arg2;  
  const int val1 = * ptr1; // get the value from the address
  const int val2 = * ptr2;
  if (val1 < val2)  { return -1; }
  if (val1 == val2) { return 0; }
  return 1;
}
int main(int argc, char * argv[])
{
  if (argc < 3)   // need two file names: input and output
    { return EXIT_FAILURE; }
  FILE * infptr;
  infptr = fopen(argv[1], "r");   // open the input file
  if (infptr == NULL)  { return EXIT_FAILURE;  }
  // count the number of integers in the file
  int count = 0;
  int val;
  while (fscanf(infptr, "%d", & val) == 1) { count ++; }
  int * arr;
  arr = malloc(sizeof(int) * count); // allocate memory for the array
  if (arr == NULL)
    {
      fclose (infptr);
      return EXIT_FAILURE;
    }
  fseek(infptr, 0, SEEK_SET); // go to the beginning of the file
  int ind = 0; // array index
  while (fscanf(infptr, "%d", & val) == 1) // fill the array
    {
      arr[ind] = val;
      ind ++;
    }
  qsort(& arr[0], count, sizeof(int), comparefunc);   // sort the array
  fclose (infptr);   // close the input file
  FILE * outfptr; 
  outfptr = fopen(argv[2], "w"); // open the output file
  if (outfptr == NULL)
    {
      free (arr); // do not forget to release memory
      return EXIT_FAILURE;
    }
  // write the sorted array to the output file
  for (ind = 0; ind < count; ind ++)
    { fprintf(outfptr, "%d\n", arr[ind]);  }
  fclose (outfptr);   // close outupt file
  free (arr);   // release the array's memory
  return EXIT_SUCCESS;
}
