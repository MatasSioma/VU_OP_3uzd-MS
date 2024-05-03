#include "pazymiai.h"
#include "gtest/gtest.h"
namespace
{

// Tests factorial of negative numbers.
TEST(One, Yes)
{
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, Factorial(-1));
}

TEST(One, Negative)
{
    EXPECT_EQ(1, 2);
}
}