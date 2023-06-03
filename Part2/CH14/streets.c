// CH14:streets.c
// implement the recursive relation for calculating the number of
// routes in a city where cars can only move northbound or eastbound
#include <stdio.h>
#include <stdlib.h>
int f(int dx, int dy) 
// No need to worry about dx < 0 or dy < 0,  already handled in main. 
{
  if ((dx == 0) || (dy == 0)) { return 1; } // Base case 
  // Recursive case 
  int a, b;
  a = f(dx - 1, dy);
  b = f(dx, dy - 1);
  return (a + b);
}
int main(int argc, char * argv[])
{
  int deltax, deltay;
  int c;
  if (argc < 3)
    {
      printf("need 2 positive integers.\n");
      return EXIT_FAILURE;
    }
  deltax = (int) strtol(argv[1], NULL, 10);
  deltay = (int) strtol(argv[2], NULL, 10);
  if ((deltax < 0) || (deltay < 0))
    {
      printf("need 2 positive integers.\n");
      return EXIT_FAILURE;
    }
  c = f(deltax, deltay);
  printf("f(%d, %d) = %d.\n", deltax, deltay, c);
  return EXIT_SUCCESS;
}
