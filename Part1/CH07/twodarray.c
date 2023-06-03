// CH07:twodarray.c
// purpose: show how to create a two-dimensional array.  The size of
// the array is 8 rows x 3 columns
#include <stdio.h>
#include <stdlib.h>
#define NUMROW 8
#define NUMCOLUMN 3
int main(int argc, char * argv[])
{
  int * * arr2d;
  int row;
  // step 1: create an array of integer pointers 
  arr2d = malloc(NUMROW * sizeof (int *));
  for (row = 0; row < NUMROW; row ++)
    {
      // step 2: for each row,  create an integer array 
      arr2d[row] = malloc(NUMCOLUMN * sizeof (int));
    }
  // now, the two-dimensional array can be used 
  arr2d[4][1] = 6;   // first index can be 0 to 7 (inclusive) 
  arr2d[6][0] = 19;  // second index can be 0 to 2 (inclusive) 
  // memory must be released in the reverse order of malloc
  for (row = 0; row < NUMROW; row ++)
    {
      free (arr2d[row]); // release the memory for each row
    }  
  free (arr2); // release the array of integer pointers
  return EXIT_SUCCESS;
}
