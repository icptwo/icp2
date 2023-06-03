// CH17:strptr1.c
#include <stdio.h>
#include <stdlib.h>
#pragma pack(1) // do not to pad any space between attributes
typedef struct
{
  char a; // assume 1 byte
  char b; // assume 1 byte
  int  c; // assume 4 byte
  double d; // assume 8 byte
  int  e; // assume 4 byte
} Bag;
int main(int argc, char * * argv)
{
  printf("sizeof(char)   = %ld\n", sizeof(char));
  printf("sizeof(int)    = %ld\n", sizeof(int));
  printf("sizeof(double) = %ld\n", sizeof(double));
  printf("sizeof(Bag)    = %ld\n", sizeof(Bag));
  Bag barray[10];
  printf("sizeof(barray) = %ld\n", sizeof(barray));
  long diff1 = (long) &(barray[1].c) - (long) & (barray[0].b);
  printf("diff1          = %ld\n", diff1);
  long diff2 = (long) &(barray[2].d) - (long) & (barray[0].c);
  printf("diff2          = %ld\n", diff2);
  // assign values to the attributes
  int ind;
  for (ind = 0; ind < 10; ind ++)
    {
      barray[ind].a = ind + 'a';
      barray[ind].b = ind + 'b';
      barray[ind].c = ind;
      barray[ind].d = 0.1 * ind;
      barray[ind].e = ind * 10;
    }
  char * chptr = & (barray[0].a);
  chptr += sizeof(Bag);
  printf("* chptr = %c\n", * chptr);
  int * intptr = & (barray[0].c);
  intptr += 9; // it means 9 * sizeof(int);
  printf("* intptr = %d\n", * intptr);
  return EXIT_SUCCESS;
}
