# Define variables
SOURCES = main.cpp pazymiai.cpp
VECTOR_SOURCES = $(SOURCES) generateVector.cpp
OTHER_SOURCES = $(SOURCES) generateOther.cpp

#default
main: $(VECTOR_SOURCES)
	g++ $(VECTOR_SOURCES) -o pazymiai

vector: $(VECTOR_SOURCES)
	@echo "\033[0;33mĮsitikinkite kad pakeitėte Container aprašą į "std::vector", pazymiai.h faile!\033[0m"
	g++ $(VECTOR_SOURCES) -o pazymiai_vector

list: $(OTHER_SOURCES)
	@echo "\033[0;33mĮsitikinkite kad pakeitėte Container aprašą į "std::list", pazymiai.h faile!\033[0m"  
	g++ $(OTHER_SOURCES) -o pazymiai_list

deque: $(OTHER_SOURCES)
	@echo "\033[0;33mĮsitikinkite kad pakeitėte Container aprašą į "std::deque", pazymiai.h faile!\033[0m"
	g++ $(OTHER_SOURCES) -o pazymiai_deque

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