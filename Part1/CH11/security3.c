// CH11:security3.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void f1(int * arr)
{
  arr[-2]  = 2016;
  arr[-1]  = -12;
}

int main(int argc, char * * argv)
{
  int x = -2;
  int arr[] = {0, 1, 2, 3, 4};
  int y = 15;
  int z = 128;
  printf("x = %d, y = %d, z = %d\n", x, y, z);
  f1(arr);
  printf("x = %d, y = %d, z = %d\n", x, y, z);
  return EXIT_SUCCESS;
}
