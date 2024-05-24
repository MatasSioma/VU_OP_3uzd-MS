#include <gtest/gtest.h>
#include "../pazymiai.h"
#include "../vector.h"

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

// Studento ir Vector klasės

TEST(VectorClass, Construct) {
    Vector<Studentas> students;
    EXPECT_EQ(0, students.size());
}

TEST(VectorClass, PushBack) {
    Vector<Studentas> students;
    students.push_back(Studentas("Jonas", "Jonaitis", 10, 9.0, 8.5, {10, 9, 8}));
    students.push_back(Studentas("Petras", "Petraitis", 9, 8.0, 7.5, {7, 8, 9}));

    EXPECT_EQ(2, students.size());
    EXPECT_EQ("Jonas", students[0].getVardas());
    EXPECT_EQ("Jonaitis", students[0].getPavarde());
    EXPECT_EQ(10, students[0].getEgz());
}

TEST(VectorClass, CopyConstructor) {
    Vector<Studentas> students;
    students.push_back(Studentas("Jonas", "Jonaitis", 10, 9.0, 8.5, {10, 9, 8}));
    Vector<Studentas> studentsCopy = students;

    EXPECT_EQ(1, studentsCopy.size());
    EXPECT_EQ("Jonas", studentsCopy[0].getVardas());
    EXPECT_EQ(10, studentsCopy[0].getEgz());
}

TEST(VectorClass, MoveConstructor) {
    Vector<Studentas> students;
    students.push_back(Studentas("Jonas", "Jonaitis", 10, 9.0, 8.5, {10, 9, 8}));
    Vector<Studentas> movedStudents = std::move(students);

    EXPECT_EQ(1, movedStudents.size());
    EXPECT_EQ(0, students.size());
    EXPECT_EQ("Jonas", movedStudents[0].getVardas());
}

TEST(VectorClass, CopyAssignment) {
    Vector<Studentas> students;
    students.push_back(Studentas("Jonas", "Jonaitis", 10, 9.0, 8.5, {10, 9, 8}));
    Vector<Studentas> studentsCopy;
    studentsCopy = students;

    EXPECT_EQ(1, studentsCopy.size());
    EXPECT_EQ("Jonas", studentsCopy[0].getVardas());
}

TEST(VectorClass, MoveAssignment) {
    Vector<Studentas> students;
    students.push_back(Studentas("Jonas", "Jonaitis", 10, 9.0, 8.5, {10, 9, 8}));
    Vector<Studentas> movedStudents;
    movedStudents = std::move(students);

    EXPECT_EQ(1, movedStudents.size());
    EXPECT_EQ(0, students.size()); // original should now be empty
    EXPECT_EQ("Jonas", movedStudents[0].getVardas());
}

TEST(VectorClass, Resize) {
    Vector<Studentas> students;
    students.push_back(Studentas("Jonas", "Jonaitis", 10, 9.0, 8.5, {10, 9, 8}));
    students.resize(5, Studentas("Petras", "Petraitis", 9, 8.0, 7.5, {7, 8, 9}));

    EXPECT_EQ(5, students.size());
    EXPECT_EQ("Petras", students[4].getVardas());
    EXPECT_EQ(9, students[4].getEgz());

    students.resize(3);
    EXPECT_EQ(3, students.size());
}

TEST(VectorClass, Clear) {
    Vector<Studentas> students;
    students.push_back(Studentas("Jonas", "Jonaitis"));
    students.clear();
    EXPECT_TRUE(students.empty());
}

TEST(VectorClass, InitializerList) {
    Vector<Studentas> students = {
        Studentas("Jonas", "Jonaitis", 10, 9.0, 8.5, {10, 9, 8}),
        Studentas("Petras", "Petraitis", 9, 8.0, 7.5, {7, 8, 9}),
        Studentas("Ona", "Onaitiene", 8, 7.5, 7.0, {6, 7, 8})
    };

    EXPECT_EQ(3, students.size());

    EXPECT_EQ("Jonas", students[0].getVardas());
    EXPECT_EQ("Jonaitis", students[0].getPavarde());
    EXPECT_EQ(10, students[0].getEgz());
    EXPECT_EQ(9.0, students[0].getVidurkis());

    EXPECT_EQ("Petras", students[1].getVardas());
    EXPECT_EQ("Petraitis", students[1].getPavarde());
    EXPECT_EQ(9, students[1].getEgz());
    EXPECT_EQ(8.0, students[1].getVidurkis());

    EXPECT_EQ("Ona", students[2].getVardas());
    EXPECT_EQ("Onaitiene", students[2].getPavarde());
    EXPECT_EQ(8, students[2].getEgz());
    EXPECT_EQ(7.5, students[2].getVidurkis());
}

TEST(VectorClass, SpeedTest) {
// TEST(VectorClass, DISABLED_SpeedTest) {
    printf("Teste iškart pateikiami 5 testų vidurkiai\n");
    unsigned int sz[5] = {10'000, 100'000, 1'000'000, 10'000'000, 100'000'000}; 
    double stlVec = 0, myVec = 0;

    for(int n = 0; n < 5; n++) {
        int realloc = 0;
        for (int i = 0; i < 5; i++) {
            realloc = 0;
            Timer stlVecT;
            std::vector<Studentas> v1;
            for (int i = 1; i <= sz[n]; ++i) {
                if(v1.capacity() == v1.size()) {
                    realloc++;
                }
                v1.push_back(Studentas());
            }
            EXPECT_EQ(v1.size(), sz[n]);
            stlVec += stlVecT.elapsed();
        }
        
        printf("%d dydžio std::vector perskirstymų sk.: %d\n", sz[n], realloc);
        realloc = 0;
        for (int i = 0; i < 5; i++) {
            realloc = 0;
            Timer myVecT;
            Vector<Studentas> v2;
            for (int i = 1; i <= sz[n]; ++i) {
                if(v2.capacity() == v2.size()) {
                    realloc++;
                }
                v2.push_back(Studentas());
            }
            EXPECT_EQ(v2.size(), sz[n]);
            myVec += myVecT.elapsed();
        }
        printf("%d dydžio mano vectoriaus perskirstymų sk.: %d\n", sz[n], realloc);

        printf("%d dydžio std::vector užpildymas: %fs\n", sz[n], stlVec / 5);
        printf("%d dydžio mano vektoriaus užpildymas: %fs\n", sz[n], myVec / 5);
    }
}