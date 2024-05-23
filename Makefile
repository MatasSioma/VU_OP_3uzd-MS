# Define variables
SOURCES = main.cpp helpers.cpp StudentaiClass.cpp vector.cpp

# Compiler and flags
CXX = g++
# CXXFLAGS = -std=c++11 -I/usr/src/googletest/include
CXXFLAGS = -I/usr/src/googletest/include


# Directories
GTEST_DIR = /usr/src/googletest
LIBS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread
# LIBS = -L$(GTEST_DIR)/lib -lgtest -pthread

# Source files
TEST_SOURCES = test/pazymiaiTest.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Default target
all: main test

# Main executable
main: $(OBJECTS)
	$(CXX) -O3 $(OBJECTS) -o pazymiai

# Test executable
test: $(TEST_OBJECTS) helpers.o StudentaiClass.o vector.o
	$(CXX) -O3 $(CXXFLAGS) $(TEST_OBJECTS) helpers.o StudentaiClass.o vector.o $(LIBS) -o test_pazymiai

clean:
	rm -f *.o test/*.o pazymiai test_pazymiai vectortest

vectortest: test/vectorTest.o vector.o StudentaiClass.o helpers.o
	$(CXX) $(CXXFLAGS) test/vectorTest.o vector.o StudentaiClass.o helpers.o $(LIBS) -o vectortest

windows: $(OBJECTS)
	x86_64-w64-mingw32-g++ -static $(OBJECTS) -o Pazymiai.exe

run:
	make clean
	make
	@echo "\n"
	./pazymiai