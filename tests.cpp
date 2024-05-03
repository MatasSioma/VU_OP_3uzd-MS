#include "pazymiai.h"
#include "gtest/gtest.h"
namespace
{

TEST(One, Yes)
{
    EXPECT_EQ(1, 1);
}

TEST(One, Negative)
{
    EXPECT_EQ(1, 2);
}
}