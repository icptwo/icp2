// CH14:fibmain.c
#include <stdio.h>
#include <stdlib.h>
#define MAXN 20
long int fib1(int n);
long int fib2(int n);
int main(int argc, char * argv[])
{
  int nval;
  for (nval = 2; nval <= MAXN; nval ++)
    {
      long int fval = fib1(nval);
      printf("fib1(%2d) = %ld\n", nval, fval);
      fval = fib2(nval);
      printf("fib2(%2d) = %ld\n", nval, fval);
    }
  return EXIT_SUCCESS;
}
