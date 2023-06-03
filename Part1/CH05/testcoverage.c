// CH05:testcoverage.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char * argv[])
{
  if (argc < 3) { return EXIT_FAILURE; }
  int x = strtol(argv[1], NULL, 10);
  int y = strtol(argv[2], NULL, 10);
  if ((x % 2) == 0)
    { printf("argv[1] is an even number\n"); }
  else
    { printf("argv[1] is an odd number\n"); }
  if ((y % 2) == 0)
    { printf("argv[2] is an even number\n"); }
  else
    { printf("argv[2] is an odd number\n"); }
  return EXIT_SUCCESS;
}
