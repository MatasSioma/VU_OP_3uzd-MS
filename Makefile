# Define variables
SOURCES = main.cpp helpers.cpp StudentaiClass.cpp

# Compiler and flags
CXX = g++
# CXXFLAGS = -std=c++11 -I/usr/src/googletest/include
CXXFLAGS = -I/usr/src/googletest/include


# Directories
GTEST_DIR = /usr/src/googletest
LIBS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread
# LIBS = -L$(GTEST_DIR)/lib -lgtest -pthread

# Source files
TEST_SOURCES = test/tests.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Default target
all: main test

# Main executable
main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o pazymiai

# Test executable
test: $(TEST_OBJECTS) helpers.o StudentaiClass.o
	$(CXX) $(CXXFLAGS) $(TEST_OBJECTS) helpers.o StudentaiClass.o $(LIBS) -o test_pazymiai

clean:
	rm -f *.o test/*.o pazymiai test_pazymiai

O1:
	g++ -O1 $(SOURCES) -o pazymiai
O2:
	g++ -O2 $(SOURCES) -o pazymiai
O3:
	g++ -O3 $(SOURCES) -o pazymiai


run:
	make clean
	make
	@echo "\n"
	./pazymiai