// demo.cpp
// demonstrate how to use rational numbers
#include <stdio.h>
#include <stdlib.h>
#include "rational.h"
int main(int argc, char *argv[])
{
  Rational r1, r2, r3, result;
  rational_init(&r1, 25, 0); // this should be invalid
  printf("r1 = "); 
  rational_print(&r1, stdout);
  rational_init(&r1, 25, 75); // should be reduced to 1/3
  printf("r1 = ");
  rational_print(&r1, stdout);
  rational_init(&r2, -100, 200); // should be reduced to -1/2
  printf("r2 = ");
  rational_print(&r2, stdout);
  rational_init(&r3, -100, -200); // should be reduced to 1/2
  printf("r3 = ");
  rational_print(&r3, stdout);
  rational_init(&r3, 0, 25); // should be reduced to 0/1
  printf("r3 = "); 
  rational_print(&r3, stdout);
  // test arithmetic operations
  printf("r1 + r2 = ");
  rational_add(&r1, &r2, &result); // 1/3 + (-1/2) = -1/6
  rational_print(&result, stdout);
  printf("r1 - r2 = ");
  rational_subtract(&r1, &r2, &result); // 1/3 - (-1/2) = 5/6
  rational_print(&result, stdout);
  printf("r1 * r2 = ");
  rational_multiply(&r1, &r2, &result); // (1/3) * -( 1/2) = -1/6
  rational_print(&result, stdout);
  printf("r1 / r2 = ");
  rational_divide(&r1, &r2, &result); // (1/3) / (-1/2) = - 2/3
  rational_print(&result, stdout);
  rational_init(&result, 1, 1);
  // exponent until it is no longer valid, r1 = 1/3
  int pwd = 1;
  while (result.valid) 
    {
      // 1/3, 1/9, 1/27 ...
      rational_multiply(&result, &r1, &result);
      printf("r1^%d = ", pwd);
      if (result.valid)
	{ rational_print(&result, stdout); }
      else
        {
	  printf("[overflow]: ");
	  rational_print(&result, stdout);
        }
      pwd ++;
    }
  rational_init(&result, 1, 1);
  // multiply until it is no longer valid, r1 = 1/3, r2 = 1/2
  pwd = 2;
  while (result.valid)
    {
      rational_multiply(&r1, &r1, &r1); // square of r1
      rational_multiply(&r2, &r2, &r2); // square of r2
      printf("r1^%d = ", pwd);
      rational_print(&r1, stdout);
      printf("r2^%d = ", pwd);
      rational_print(&r2, stdout);
      rational_add(&r1, &r2, &result);
      printf("result = ");      
      if (result.valid)
	{ rational_print(&result, stdout); }
      else
        {
	  printf("[overflow]: ");
	  rational_print(&result, stdout);
        }
      pwd *= 2;
    }
  return EXIT_SUCCESS;
}
