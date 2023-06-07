// CH08:qsort/main.c
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RANGE 10000
int compareint(const void * arg1, const void * arg2);
void printArray(int * arr, int size)
{
  int ind;
  for (ind = 0; ind < size; ind ++) { printf("%d ", arr[ind]); }
  printf("\n");
}
int main(int argc, char * * argv)
{
  if (argc != 2) { return EXIT_FAILURE; }
  int size = strtol(argv[1], NULL, 10);
  if (size <= 0) { return EXIT_FAILURE; }    
  int * arr;
  arr = malloc(sizeof(int) * size);
  if (arr == NULL) { return EXIT_FAILURE; }
  int ind;
  srand(time(NULL)); // set the seed
  for (ind = 0; ind < size; ind ++) // create a test case
    { arr[ind] = rand() % RANGE; }
  printArray(arr, size);
  qsort(& arr[0], size, sizeof(int), compareint);
  printArray(arr, size);
  free (arr);
  return EXIT_SUCCESS;
}
