// CH14:factorial2.c
#include <stdio.h>
#include <stdlib.h>
#define MAXN 20
long int fac2(int n)
{
  if (n < 0)
    {
      printf("n cannot be negative\n");
      return 0;
    }
  if (n == 0) { return 1; }
  long int result = 1;
  while (n > 0)
    {
      result *= n;
      n --;
    }
  return result;
}
int main(int argc, char * argv[])
{
  int nval;
  for (nval = 0; nval <= MAXN; nval ++)
    {
      long int fval = fac2(nval);
      printf("fac2(%2d) = %ld\n", nval, fval);
    }
  return EXIT_SUCCESS;
}
