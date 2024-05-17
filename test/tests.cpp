#include <gtest/gtest.h>
#include "../pazymiai.h"

int ndSk = 5, studSk = 30, inputOption = 3;

TEST(StudentasKlase, ConstructorWithNames) {
    Studentas stud;
    stud.setVardas("Matas");
    stud.setPavarde("Semenas");
    EXPECT_EQ(stud.getVardas(), "Matas");
    EXPECT_EQ(stud.getPavarde(), "Semenas");
}

//Konstruktoriaus testas
TEST(StudentasKlase, DefaultConstructor) {
    Studentas stud;
    EXPECT_EQ(stud.getVardas(), "BeVardis");
    EXPECT_EQ(stud.getPavarde(), "BePavardis");
}
//Move konstruktoriaus testas
TEST(StudentasKlase, MoveConstructor) {
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
TEST(StudentasKlase, CopyConstructor) {
    Studentas stud;
    stud.setVardas("Matas");
    stud.setPavarde("Semenas");
    Studentas stud2(stud);
    EXPECT_EQ(stud2.getVardas(), "Matas");
    EXPECT_EQ(stud2.getPavarde(), "Semenas");
    EXPECT_EQ(stud.getVardas(), stud2.getVardas());
}
//Assign operatoriaus testas
TEST(StudentasKlase, Assignment) {
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
TEST(StudentasKlase, MoveAssignment) {
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