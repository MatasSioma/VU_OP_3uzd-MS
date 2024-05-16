#include <gtest/gtest.h>
#include "../pazymiai.h"

int ndSk = 5, studSk = 30, inputOption = 3;

int Add(int a, int b) {
    return a + b;
}
TEST(AdditionTest, HandlesPositiveInput) {
    EXPECT_EQ(Add(1, 2), 3);
}

TEST(StudentasKlase, Konstruktorius) {
    Studentas a("Matas", "Semenas");
    EXPECT_EQ(a.getVardas(), "Matas");
}

TEST(StudentasKlase, kopija) {
    Studentas stud1("Matas", "Semenas");
    Studentas stud2 = stud1;

    EXPECT_EQ(stud1.getVardas(), stud2.getVardas());
    EXPECT_EQ(stud1.getPavarde(), stud2.getPavarde());
}
