#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "rational.h"
static long long_gcd(long a, long b)
{
  if ((a == 0) && (b == 0))
    { return 0; }
  if (b == 0)
    { return labs(a); }
  else
    { return long_gcd(b, a % b); }
}
static void reduce_fraction(Rational *number)
{
  long common_divisor = long_gcd(number->num, number->den);
  if ((common_divisor) == 0)
    { return; }
  // neither denominator nor numerator is zero
  number->num /= common_divisor;
  number->den /= common_divisor;
  if ((number->den) < 0)
    {
      number->den = - number->den;
      number->num = - number->num;
    }
}
static void rational_internal_init(Rational *number,
                                   long num, long den)
{
  number->num = num;
  number->den = den;
  if (den == 0)
    {
      number -> valid = false;
      return; 
    }
  else
    { number -> valid = true; }
  reduce_fraction(number);
}
void rational_init(Rational *number, long num, long den)
{
  rational_internal_init(number, num, den);
}
void rational_from_rational(Rational *dest, const Rational *src)
{
  rational_internal_init(dest, src->num, src->den);
}
void rational_from_long(Rational *number, long den)
{
  rational_internal_init(number, den, 1L);
}
long rational_numerator(Rational *number)
{
  return number->num;
}
long rational_denominator(Rational *number)
{
  return number->den;
}
void rational_print(const Rational *number, FILE *stream)
{
  fprintf(stream, "%ld/%ld (valid=%d)\n",
	  number->num, number->den, number->valid);
}
bool long_add(long a, long b, long *c)
{
  return __builtin_saddl_overflow(a, b, c); // true: overflow
}
bool long_multiply(long a, long b, long *c)
{
  return __builtin_smull_overflow(a, b, c); // true: overflow
}
bool long_subtract(long a, long b, long *c)
{
  return __builtin_ssubl_overflow(a, b, c); // true: overflow
}
static void rational_add_sub(const Rational *n1, const Rational *n2,
			     Rational * result, bool addition)
{
  // used by both add and sub
  // addition: true; subtraction: false
  /*
     n1->num     n2->num     
    --------- +- --------- = 
     n1->den     n2->den     

     (n1->num) * (n2->den) +- (n2->num) * (n1->den) 
     -----------------------------------------------
                 (n1->den) * (n2->den)
   */
  /*
    The result is invalid, if 
    either n1 or n2 is invalid, or
    the numerator or the denominator overflows.
   */
  if (((n1->valid) == false) || ((n2->valid) == false))
    {
      result->valid = false;
      return;
    }
  long den1den2; // (n1->den) * (n2->den)
  long num1den2; // (n1->num) * (n2->den)
  long num2den1; // (n2->num) * (n1->den)
  long num;      // (n1->num) * (n2->den) +- (n2->num) * (n1->den)
  bool overflow1, overflow2, overflow3, overflow4;
  overflow1 = long_multiply(n1->den, n2->den, & den1den2);
  overflow2 = long_multiply(n1->num, n2->den, & num1den2);
  overflow3 = long_multiply(n2->num, n1->den, & num2den1);
  if (addition == true)
    { overflow4 = long_add(num1den2, num2den1, & num); }
  else
    { overflow4 = long_subtract(num1den2, num2den1, & num); }
  bool overflow = overflow1 || overflow2 || overflow3 || overflow4;
  if (overflow == true)
    {
      result->valid = false;
      return;
    }
  rational_internal_init(result, num, den1den2);
}
void rational_add(const Rational *n1, const Rational *n2, Rational *result)
{
  rational_add_sub(n1, n2, result, true);
}
void rational_subtract(const Rational *n1, const Rational *n2, Rational *result)
{
  rational_add_sub(n1, n2, result, false);
}
void rational_multiply(const Rational *n1, const Rational *n2, Rational *result)
{
  if (((n1->valid) == false) || ((n2->valid) == false))
    {
      result->valid = false;
      return;
    }
  long den1den2;
  long num1num2;
  bool overflow1, overflow2;
  overflow1 = long_multiply(n1->num, n2->num, &num1num2);
  overflow2 = long_multiply(n1->den, n2->den, &den1den2);
  if ((overflow1 == true) || (overflow2 == true))
    {
      result->valid = false;
      return;
    }
  rational_internal_init(result, num1num2, den1den2);
}
void rational_divide(const Rational *n1, const Rational *n2, Rational *result)
{
  if (((n1->valid) == false) || ((n2->valid) == false) ||
      ((n2->num) == 0))
    {
      result->valid = false;
      return;
    }
  long num1den2, den1num2;
  bool overflow1, overflow2;
  overflow1 = long_multiply(n1->num, n2->den, &num1den2);
  overflow2 = long_multiply(n2->num, n1->den, &den1num2);
  if ((overflow1 == true) || (overflow2 == true))
    {
      result->valid = false;
      return;
    }
  rational_internal_init(result, num1den2, den1num2);
}
void rational_compare(const Rational *n1, const Rational *n2, int *result)
{
  // result = -1 if (n1) < (n2)
  // result = 0 if (n1) == (n2)
  // result = 1 if (n1) > (n2)
  // result = 2 if either n1 or n2 is valid or overflow
  Rational diff;
  rational_subtract(n1, n2, & diff);
  if ((diff.valid) == false)
    {
      * result = 2;
      return;
    }
  if ((diff.num) < 0)
    {
      * result = -1;
      return;
    }
  if ((diff.num) == 0)
    {
      * result = 0;
      return;
    }
  * result = 1;
}
