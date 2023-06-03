// CH14:factorial1.c
#include <stdio.h>
#include <stdlib.h>
#define MAXN 20
long int fac(int n)
{
  if (n < 0)
    {
      printf("n cannot be negative\n");
      return 0;
    }
  if (n == 0) { return 1; } // Base case 
  /* Recursive case */
  return n * fac(n - 1);
}
int main(int argc, char * argv[])
{
  int nval;
  for (nval = 0; nval <= MAXN; nval ++)
    {
      long int fval = fac(nval);
      printf("fac(%2d) = %ld\n", nval, fval);
    }
  return EXIT_SUCCESS;
}
