#include <gtest/gtest.h>
#include "../vector.h"
#include "../timer.h"

#include <iostream>
#include <stdexcept>

int ndSk = 5, studSk = 30, inputOption = 3;

TEST(nextCap, correctBehaviuor) {
    EXPECT_EQ(nextCapacity(4), 4);
    EXPECT_EQ(nextCapacity(4+1), 8);
    EXPECT_EQ(nextCapacity(0), 0);
}

TEST(VectorClass, DefaultConstructor) {
    Vector<int> a;
    EXPECT_TRUE(a.empty());
    EXPECT_EQ(0, a.size());
    EXPECT_EQ(0, a.capacity());
}

TEST(VectorClass, InitializerListConstructor) {
    Vector<int> a{1, 2, 3};
    EXPECT_FALSE(a.empty());
    EXPECT_EQ(3, a.size());
    EXPECT_GE(a.capacity(), a.size());
    EXPECT_EQ(1, a[0]);
    EXPECT_EQ(2, a[1]);
    EXPECT_EQ(3, a[2]);
}

TEST(VectorClass, CopyConstructor) {
    Vector<int> original{1, 2, 3};
    Vector<int> copy = original;
    EXPECT_EQ(copy.size(), original.size());
    for (size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(copy[i], original[i]);
    }
}

TEST(VectorClass, MoveConstructor) {
    Vector<int> original{1, 2, 3};
    Vector<int> moved = std::move(original);
    EXPECT_TRUE(original.empty());
    EXPECT_EQ(3, moved.size());
    EXPECT_EQ(1, moved[0]);
    EXPECT_EQ(2, moved[1]);
    EXPECT_EQ(3, moved[2]);
}

TEST(VectorClass, CopyAssignmentOperator) {
    Vector<int> original{1, 2, 3};
    Vector<int> assigned;
    assigned = original;
    EXPECT_EQ(assigned.size(), original.size());
    for (size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(assigned[i], original[i]);
    }
}

TEST(VectorClass, MoveAssignmentOperator) {
    Vector<int> original{1, 2, 3};
    Vector<int> moved;
    moved = std::move(original);
    EXPECT_TRUE(original.empty());
    EXPECT_EQ(3, moved.size());
    EXPECT_EQ(1, moved[0]);
    EXPECT_EQ(2, moved[1]);
    EXPECT_EQ(3, moved[2]);
}

TEST(VectorClass, AtMethod) {
    Vector<int> a{1, 2, 3};
    EXPECT_EQ(1, a.at(0));
    EXPECT_EQ(2, a.at(1));
    EXPECT_EQ(3, a.at(2));
    EXPECT_THROW(a.at(3), std::out_of_range);
}

TEST(VectorClass, PushBack) {
    Vector<int> a;
    a.push_back(1);
    a.push_back(2);
    EXPECT_EQ(2, a.size());
    EXPECT_EQ(1, a[0]);
    EXPECT_EQ(2, a[1]);
}

TEST(VectorClass, EmplaceBack) {
    Vector<std::string> a;
    a.emplace_back("hello");
    a.emplace_back("world");
    EXPECT_EQ(2, a.size());
    EXPECT_EQ("hello", a[0]);
    EXPECT_EQ("world", a[1]);
}

TEST(VectorClass, Resize) {
    Vector<int> a;
    a.resize(5, 42);
    EXPECT_EQ(5, a.size());
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(42, a[i]);
    }
    a.resize(3);
    EXPECT_EQ(3, a.size());
    EXPECT_EQ(42, a[0]);
    EXPECT_EQ(42, a[1]);
    EXPECT_EQ(42, a[2]);
}

TEST(VectorClass, Clear) {
    Vector<int> a{1, 2, 3};
    a.clear();
    EXPECT_TRUE(a.empty());
}

TEST(VectorClass, PopBack) {
    Vector<int> a{1, 2, 3};
    a.pop_back();
    EXPECT_EQ(2, a.size());
    EXPECT_EQ(1, a[0]);
    EXPECT_EQ(2, a[1]);
}

// Testas paimtas is https://en.cppreference.com/w/cpp/container/vector/shrink_to_fit
TEST(VectorClass, CapacityBehavior) {
    Vector<int> v;
    EXPECT_EQ(v.capacity(), 0) << "Default-constructed capacity is not zero.";

    v.resize(100);
    EXPECT_EQ(v.capacity(), 100) << "Capacity of a 100-element vector is not 100.";

    v.resize(50);
    EXPECT_EQ(v.capacity(), 100) << "Capacity after resize(50) should still be 100.";

    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 50) << "Capacity after shrink_to_fit() is not 50.";

    v.clear();
    EXPECT_EQ(v.capacity(), 50) << "Capacity after clear() should still be 50.";

    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 0) << "Capacity after second shrink_to_fit() is not 0.";

    for (int i = 0; i < 300; ++i)
        v.push_back(i);
    EXPECT_GE(v.capacity(), 300) << "Capacity after adding 300 elements is less than 300.";

    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 300) << "Capacity after final shrink_to_fit() is not 300.";
}

TEST(VectorClass, SpeedTest) {
// TEST(VectorClass, DISABLED_SpeedTest) {
    printf("Teste iškart pateikiami 5 testų vidurkiai\n");
    unsigned int sz[5] = {10'000, 100'000, 1'000'000, 10'000'000, 100'000'000}; 
    double stlVec = 0, myVec = 0;
    for(int n = 0; n < 5; n++) {
        for (int i = 0; i < 5; i++) {
            Timer stlVecT;
            std::vector<int> v1;
            for (int i = 1; i <= sz[n]; ++i)
            v1.push_back(i);
            EXPECT_EQ(v1.size(), sz[n]);
            stlVec += stlVecT.elapsed();
        }
        
        for (int i = 0; i < 5; i++) {
            Timer myVecT;
            Vector<int> v2;
            for (int i = 1; i <= sz[n]; ++i)
            v2.push_back(i);
            EXPECT_EQ(v2.size(), sz[n]);
            myVec += myVecT.elapsed();
        }
        
        printf("%d dydžio std::vector užpildymas: %fs\n", sz[n], stlVec / 5);
        printf("%d dydžio mano vektoriaus užpildymas: %fs\n", sz[n], myVec / 5);
    }
}