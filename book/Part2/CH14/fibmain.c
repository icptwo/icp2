// CH14:fibmain.c
#include <stdio.h>
#include <stdlib.h>
#define MAXN 20
#define REPEAT 100000
long int fib1(int n);
long int fib2(int n);
int main(int argc, char * argv[])
{
  int nval, iter;
  for (iter = 0; iter < REPEAT; iter ++)
    {
      for (nval = 1; nval <= MAXN; nval ++)
	{
	  long int fval1 = fib1(nval);
	  // printf("fib1(%2d) = %ld\n", nval, fval1);
	  long int fval2 = fib2(nval);
	  // printf("fib2(%2d) = %ld\n", nval, fval2);
	  if (fval1 != fval2)
	    {
	      printf("ERROR, fval1 = %ld, fval2 = %ld\n",
		     fval1, fval2);
	    }
	}
    }
  return EXIT_SUCCESS;
}
