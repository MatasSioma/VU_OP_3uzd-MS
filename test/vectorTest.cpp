#include <gtest/gtest.h>
#include "../vector.h"
#include <iostream>

TEST(VectorClass, defaultConstructor) {
    Vector<int> a;
    EXPECT_TRUE(a.empty());
}