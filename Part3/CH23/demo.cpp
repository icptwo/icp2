// demo.cpp
// use rational numbers
#include <stdio.h>
#include <stdlib.h>
#include "rational.h"
int main(int argc, char *argv[])
{
  Rational r1, r2, r3, result;
  rational_init(&r1, 25, 0);
  printf("r1 = "); 
  rational_print(&r1, stdout);
  rational_init(&r1, 25, 75);
  printf("r1 = ");
  rational_print(&r1, stdout);
  rational_init(&r2, -100, 200);
  printf("r2 = ");
  rational_print(&r2, stdout);
  rational_init(&r3, -100, -200);
  printf("r3 = ");
  rational_print(&r3, stdout);
  rational_init(&r3, 0, 25);
  printf("r3 = "); 
  rational_print(&r3, stdout);
  printf("r1 + r2 = ");
  rational_add(&r1, &r2, &result);
  rational_print(&result, stdout);
  printf("r1 - r2 = ");
  rational_subtract(&r1, &r2, &result);
  rational_print(&result, stdout);
  printf("r1 * r2 = ");
  rational_multiply(&r1, &r2, &result);
  rational_print(&result, stdout);
  printf("r1 / r2 = ");
  rational_divide(&r1, &r2, &result);
  rational_print(&result, stdout);
  rational_init(&result, 1, 1);
  int pwd = 1;
  while (result.valid) 
    {
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
  pwd = 2;
  while (result.valid)
    {
      rational_multiply(&r1, &r1, &r1);
      rational_multiply(&r2, &r2, &r2);
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
