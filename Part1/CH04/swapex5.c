// CH04:swap5ex.c
#include <stdio.h>
#include <stdlib.h>
void swap5 (int * a, int * b)
{
  int k = a;
  a = b;
  b = k;
}
int main (int argc ,char * * argv)
{
  int u;
  int t;
  u = 17;
  t = -96;
  printf ("before swap5: u = %d , t = %d \n" , u , t);
  swap5 (& u , * t);
  printf ("after  swap5: u = %d , t = %d \n" , u , t);
  return EXIT_SUCCESS;
}
