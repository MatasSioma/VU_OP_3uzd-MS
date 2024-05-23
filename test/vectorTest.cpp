#include <gtest/gtest.h>
#include "../vector.h"
#include <iostream>
#include <stdexcept>

TEST(nextCap, correctBehaviuor) {
    EXPECT_EQ(nextCapacity(4), 4);
    EXPECT_EQ(nextCapacity(4+1), 8);
    EXPECT_EQ(nextCapacity(0), 0);
}

TEST(VectorClass, defaultConstructor) {
    Vector<int> a;
    EXPECT_TRUE(a.empty());
}

TEST(VectorClass, defaultConstructorasd) {
    Vector<int> a {1,2,3};
    EXPECT_THROW({
        a.at(4);
    }, std::out_of_range);
}