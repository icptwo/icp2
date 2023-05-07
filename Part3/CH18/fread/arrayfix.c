// CH18:fread/arrayfix.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma pack(1) // tell compiler not to pad any space
typedef struct
{
  int length;
  int * data;
} Array;
int main(int argc, char **argv)
{
  int length = 10;
  char * filename = "data";
  Array * aptr1 = NULL;
  printf("sizeof(aptr1) = %d\n", (int) sizeof(aptr1));
  aptr1 = malloc(sizeof(Array));
  printf("sizeof(aptr1) = %d, sizeof(Array) = %d\n", 
	 (int) sizeof(aptr1), (int) sizeof(Array));
  aptr1 -> length = length;
  aptr1 -> data = malloc(sizeof(int) * (aptr1 -> length));
  printf("sizeof(aptr1): %d, sizeof(aptr1 -> data): %d\n", 
	 (int) sizeof(aptr1), (int) sizeof(aptr1 -> data));
  int ind;
  for (ind = 0; ind < (aptr1 -> length); ind ++)
    { aptr1 -> data[ind] = ind; } // 0, 1, 2, ..., 9
  FILE * fptr = fopen(filename, "w");
  // write the length
  if (fwrite(& (aptr1 -> length), sizeof(int), 1, fptr) != 1)
    { return EXIT_FAILURE; } // fwrite fail
  // write the data
  if (fwrite((aptr1 -> data), sizeof(int), length, fptr) != length)
    { return EXIT_FAILURE; } // fwrite fail
  printf("ftell(fptr) = %d\n", (int) ftell(fptr));
  fclose (fptr);
  srand(time(NULL)); // set the seed of the random number
  for (ind = 0; ind < (aptr1 -> length); ind ++)
    { aptr1 -> data[ind] = rand();  }
  // read the data from the file
  Array * aptr2 = NULL;
  aptr2 = malloc(sizeof(Array));
  fptr = fopen(filename, "r");
  if (fread(& (aptr2 -> length), sizeof(int), 1, fptr) != 1)
    { return EXIT_FAILURE; }
  aptr2 -> data = malloc(sizeof(int) * (aptr2 -> length));  
  if (fread((aptr2 -> data), sizeof(int), aptr2 -> length, fptr) != length)
    { return EXIT_FAILURE; } 
  int sum = 0;
  for (ind = 0; ind < (aptr2 -> length); ind ++)
    { sum += aptr2 -> data[ind]; }
  printf("sum = %d\n", sum);
  free(aptr2 -> data);
  free(aptr2);
  free(aptr1 -> data);
  free(aptr1);
  return EXIT_SUCCESS;
}
