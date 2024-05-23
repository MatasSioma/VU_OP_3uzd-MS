#include <gtest/gtest.h>
#include "../pazymiai.h"

int ndSk = 5, studSk = 30, inputOption = 3;

TEST(RuleOfFiveStudentas, ConstructorWithNames) {
    Studentas stud;
    stud.setVardas("Matas");
    stud.setPavarde("Semenas");
    EXPECT_EQ(stud.getVardas(), "Matas");
    EXPECT_EQ(stud.getPavarde(), "Semenas");
}

//Konstruktoriaus testas
TEST(RuleOfFiveStudentas, DefaultConstructor) {
    Studentas stud;
    EXPECT_EQ(stud.getVardas(), "BeVardis");
    EXPECT_EQ(stud.getPavarde(), "BePavardis");
}
//Move konstruktoriaus testas
TEST(RuleOfFiveStudentas, MoveConstructor) {
    Studentas stud;
    stud.setVardas("Matas");
    stud.setPavarde("Semenas");
    Studentas stud2(std::move(stud));
    EXPECT_EQ(stud2.getVardas(), "Matas");
    EXPECT_EQ(stud2.getPavarde(), "Semenas");
    GTEST_EXPECT_FALSE(stud.getVardas() == stud2.getVardas());
    EXPECT_TRUE(stud.getVardas().empty());
    EXPECT_TRUE(stud.getPavarde().empty());
}
//Copy konstruktoriaus testas
TEST(RuleOfFiveStudentas, CopyConstructor) {
    Studentas stud;
    stud.setVardas("Matas");
    stud.setPavarde("Semenas");
    Studentas stud2(stud);
    EXPECT_EQ(stud2.getVardas(), "Matas");
    EXPECT_EQ(stud2.getPavarde(), "Semenas");
    EXPECT_EQ(stud.getVardas(), stud2.getVardas());
}
//Assign operatoriaus testas
TEST(RuleOfFiveStudentas, Assignment) {
    Studentas stud;
    stud.setVardas("Matas");
    stud.setPavarde("Semenas");
    Studentas stud2;
    stud2 = stud;
    EXPECT_EQ(stud2.getVardas(), "Matas");
    EXPECT_EQ(stud2.getPavarde(), "Semenas");
    EXPECT_EQ(stud.getVardas(), stud2.getVardas());
}
//Perkelimo priskyrimo operatoriaus testas
TEST(RuleOfFiveStudentas, MoveAssignment) {
    Studentas stud;
    stud.setVardas("Matas");
    stud.setPavarde("Semenas");
    Studentas stud2;
    stud2 = std::move(stud);
    EXPECT_EQ(stud2.getVardas(), "Matas");
    EXPECT_EQ(stud2.getPavarde(), "Semenas");
    GTEST_EXPECT_FALSE(stud.getVardas() == stud2.getVardas());
    EXPECT_TRUE(stud.getVardas().empty());
    EXPECT_TRUE(stud.getPavarde().empty());
}