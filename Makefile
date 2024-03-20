# Define variables
SOURCES = main.cpp pazymiai.cpp
VECTOR_SOURCES = $(SOURCES) generateVector.cpp
LIST_SOURCES = $(SOURCES) generateList.cpp
DEQUE_SOURCES = $(SOURCES) generateDeque.cpp

#default
main: $(VECTOR_SOURCES)
	g++ $(VECTOR_SOURCES) -o pazymiai

vector: $(VECTOR_SOURCES)
	g++ $(VECTOR_SOURCES) -o pazymiai_vector

list: $(LIST_SOURCES)
	g++ $(LIST_SOURCES) -o pazymiai_list

deque: $(DEQUE_SOURCES)
	g++ $(DEQUE_SOURCES) -o pazymiai_deque

all:
	make vector
	make list
	make deque


clean:
	rm -f pazymiai pazymiai_vector pazymiai_list pazymiai_deque

run:
	make clean
	make
	./pazymiai