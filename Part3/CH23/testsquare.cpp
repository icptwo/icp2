// CH23:testsquare.cpp
#include <gtest/gtest.h>
double square (const double val);
TEST(SquarTest, PositiveNumbers)
{ 
    EXPECT_EQ (324, square (18.0));
    EXPECT_EQ (625, square (25));
    EXPECT_EQ (49,  square (7.0));
    // EXPECT_EQ (52,  square (6.3)); // fail
}
TEST(SquarTest, NegativeNumbers)
{ 
    EXPECT_EQ (64, square (-8.0));
    EXPECT_EQ (841, square (-29));
    EXPECT_EQ (49,  square (-7.0));
    // EXPECT_EQ (133,  square (-9.4)); // fail
}
int main(int argc, char ** argv)
{
  testing::InitGoogleTest(& argc, argv);
  return RUN_ALL_TESTS();
}
