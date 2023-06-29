// CH07:twodarraycontiguous.c
// purpose: show how to create a two-dimensional array.  The size of
// the array is 8 rows x 3 columns
// This version ensures that the allocation is contiguous.
// That is, all of the "rows" are located in a single allocated block of memory
#include <stdio.h>
#include <stdlib.h>
#define NUMROW 8
#define NUMCOLUMN 3
int main(int argc, char * argv[])
{
  int * * arr2d;
  int * arr2d_data;
  int row;
  // step 1: create an array of integer pointers 
  arr2d = malloc(NUMROW * sizeof (int *));
  // step 1a: create an array of NUMROWS * NUMCOLUMN integers
  // all row data is allocated as a single block of data
  arr2d_data = malloc(NUMROW * NUMCOLUMN * sizeof(int));
  for (row = 0; row < NUMROW; row ++)
    {
      // step 2: for each row, initialize to an offset of the underlying 1d array
      arr2d[row] = arr2d_data + row * NUMCOLUMN;
    }
  // now, the two-dimensional array can be used 
  arr2d[4][1] = 6;   // first index can be 0 to 7 (inclusive) 
  arr2d[6][0] = 19;  // second index can be 0 to 2 (inclusive) 
  // memory must be released in the reverse order of malloc
  free (arr2d); // release the array of integer pointers
  free (arr2d_data); // release the array for 1d array of integer
  return EXIT_SUCCESS;
}
