// CH17:structsize.c
#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)
// tell compiler not to pad any space between
// attributes in structure
// assume the size of the data types
// char:    1 byte
// int:     4 bytes
// double:  8 bytes
// pointer: 8 bytes
#define NUMVECTOR 10
typedef struct
{
  int x;
  int y;
  int z;
  double t;
} Vector;
int main(int argc, char ** argv)
{
  Vector varr[NUMVECTOR];
  printf("%ld\n", sizeof(varr)); 
  Vector * vptr;
  vptr = & varr[0];
  printf("%ld\n", sizeof(vptr)); 
  int ind;
  for (ind = 0; ind < NUMVECTOR; ind ++)
    {
      varr[ind].x = ind;
      varr[ind].y = ind * 2;
      varr[ind].z = ind * 3;
      varr[ind].t = ind * 4.0;
    }
  vptr = malloc(sizeof(Vector) * 100);
  FILE * fptr = fopen("data", "w");
  // assume fopen succeeds
  fwrite(varr, sizeof(Vector), NUMVECTOR, fptr);
  fclose (fptr);
  fptr = fopen("data", "r");
  int rtv = fseek(fptr, 48, SEEK_SET);
  if (rtv != 0)
    {
      fclose (fptr);
      return EXIT_FAILURE;
    }
  // assume fseek succeeds
  int a = -2019;
  rtv = fread(& a, sizeof(int), 1, fptr);
  if (rtv == 0)
    {
      fclose (fptr);
      return EXIT_FAILURE;
    }
  printf("%d\n", a); 
  Vector v;
  v = varr[3];
  v.x = -264;
  printf("%d\n", varr[3].x - v.x); 
  free (vptr);
  printf("%d\n", (vptr == NULL));
  // please notice ==, it is not = 
  return EXIT_SUCCESS;
}
