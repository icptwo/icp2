// CH14:countfib2.c
#include <stdio.h>
#include <stdlib.h>
long int fib(int n, long int * count)
{
  (* count) ++;
  if (n == 1) { return 1; }
  if (n == 2) { return 1; }
  long int a;
  long int b;
  int m = n / 2;
  if ((n % 2) == 0) // n is even number
    {
      // a = fib(m + 1, count); // no need to call fib
      b = fib(m, count);
      long int c = fib(m - 1, count);
      a = b + c; // compute a from b and c
      return (a * b + b * c);
    }
  // n is odd number
  a = fib(m + 1, count);
  b = fib(m, count);
  return (a * a + b * b);
}
int main(int argc, char * * argv)
{
  int n;
  for (n = 2; n <= 30; n ++)
    {
      long int count = 0;
      long int result = fib(n, & count);
      printf("n = %d, result = %ld, count = %ld\n", n, result, count);
    }
  return EXIT_SUCCESS;
}
