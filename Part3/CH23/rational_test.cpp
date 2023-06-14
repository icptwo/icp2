// CH23:rational_test.cpp
#include <gtest/gtest.h>
#include <limits.h>
#include "rational.h"
TEST(RationalTest, Long)
{
  long a, b, c, success;
  // LONG_MAX: add and subtract
  a = LONG_MAX;
  b = 1;
  ASSERT_TRUE(long_add(a, b, &c));       // overflow
  ASSERT_FALSE(long_subtract(a, b, &c)); // no overflow
  ASSERT_FALSE(long_multiply(a, b, &c)); // no overflow
  // LONG_MIN: add and subtract
  a = LONG_MIN;
  ASSERT_TRUE(long_subtract(a, b, &c));  // underflow
  ASSERT_FALSE(long_add(a, b, &c));      // no underflow
  ASSERT_FALSE(long_multiply(a, b, &c)); // no underflow
  // multiply
  a = LONG_MAX;
  b = 2;
  EXPECT_TRUE(long_multiply(a, b, &c)); // overflow
  a = LONG_MIN;
  EXPECT_TRUE(long_multiply(a, b, &c)); // underflow
  // small numbers
  a = 25;
  b = 35;
  // The following test will fail, should not overflow (thus, false)
  // EXPECT_TRUE(long_add(a, b, &c));      
  // EXPECT_TRUE(long_subtract(a, b, &c)); 
  // EXPECT_TRUE(long_multiply(a, b, &c)); 
}
TEST(RationalTest, Initialization)
{
  Rational r1, r2, r3;
  rational_init(&r1, 1, 2);
  rational_init(&r2, 300, 400);
  EXPECT_EQ(rational_numerator(&r1), 1L);
  EXPECT_EQ(rational_denominator(&r1), 2L);
  EXPECT_EQ(rational_numerator(&r2), 3L);
  EXPECT_EQ(rational_denominator(&r2), 4L);
  rational_from_rational(&r3, &r1);
  EXPECT_EQ(rational_numerator(&r3), 1L);
  EXPECT_EQ(rational_denominator(&r3), 2L);
  rational_from_long(&r3, 4L);
  // EXPECT_NE(rational_numerator(&r3), 4L); // should be EQ
  // EXPECT_NE(rational_denominator(&r3), 1L); // should be EQ
}
TEST(RationalTest, Compare)
{
  Rational r1, r2, r3;
  rational_init(&r1, 1, 2);
  rational_init(&r2, 300, 400);
  rational_init(&r3, 3, 4);
  int result;
  rational_compare(&r1, &r2, &result); // 1/2 < 3/4, result is -1
  EXPECT_LT(result, 0);
  rational_compare(&r3, &r2, &result); // result is -1
  EXPECT_EQ(result, 0);
  rational_init(&r2, 3, 0); // invalid
  rational_compare(&r3, &r2, &result); // result is 2
  EXPECT_GT(result, 1);  
  rational_from_rational(&r2, &r3); // r2 same as r3, result is 0
  rational_compare(&r3, &r2, &result);
  // The following should fail
  // EXPECT_EQ(result, 1); 
}
TEST(RationalTest, Add)
{
  Rational r1, r2, expected, result;
  int comparison;
  rational_init(&r1, 1, 2);
  rational_init(&r2, -1, 4);
  rational_init(&expected, 1, 4);
  rational_add(&r1, &r2, &result); // 1/2 + (-1/4) = 1/4
  rational_compare(&result, &expected, &comparison);
  EXPECT_EQ(comparison, 0);
  rational_init(&r1, LONG_MAX, 2);
  rational_init(&r2, 1, 2);
  rational_add(&r1, &r2, &result);
  rational_compare(&result, &expected, &comparison);
  EXPECT_EQ(comparison, 2);
}
TEST(RationalTest, Subtract)
{
  Rational r1, r2, expected, result;
  int comparison;
  rational_init(&r1, 2, 3);
  rational_init(&r2, -1, 6);
  rational_init(&expected, 5, 6);
  rational_subtract(&r1, &r2, &result);
  rational_compare(&result, &expected, &comparison);
  EXPECT_EQ(comparison, 0);
}
TEST(RationalTest, Multiply)
{
  Rational r1, r2, expected, result;
  int comparison;
  rational_init(&r1, 2, 3);
  rational_init(&r2, -30, -20);
  rational_init(&expected, 1, 1);
  rational_multiply(&r1, &r2, &result);
  rational_compare(&result, &expected, &comparison);
  EXPECT_EQ(comparison, 0);
}
TEST(RationalTest, Divide)
{
  Rational r1, r2, expected, result;
  int comparison;
  rational_init(&r1, -2, 3);
  rational_init(&r2, 2000, -3000);
  rational_init(&expected, 1, 1);
  rational_divide(&r1, &r2, &result);
  rational_compare(&result, &expected, &comparison);
  EXPECT_EQ(comparison, 0);
}
int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
