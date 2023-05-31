// CH22:rational.h
#ifndef RATIONAL_H
#define RATIONAL_H
#include <stdio.h>
#include <stdbool.h>
typedef struct
{
  long num;   // numerator
  long den;   // denominator
  bool valid; // false if denominator is zero or overflow
} Rational;
void rational_init(Rational *number, long num, long den);
void rational_from_rational(Rational *dest, const Rational *src);
void rational_from_long(Rational *number, long num);
long rational_numerator(Rational *number);
long rational_denominator(Rational *number);
void rational_print(const Rational *number, FILE *stream);
void rational_add(const Rational *n1, const Rational *n2,
		  Rational *result);
void rational_subtract(const Rational *n1, const Rational *n2,
		       Rational *result);
void rational_multiply(const Rational *n1, const Rational *n2,
		       Rational *result);
void rational_divide(const Rational *n1, const Rational *n2,
		     Rational *result);
void rational_compare(const Rational *n1, const Rational *n2,
		      int *result);
bool long_add(long a, long b, long *c);
bool long_multiply(long a, long b, long *c);
bool long_subtract(long a, long b, long *c);
#endif
