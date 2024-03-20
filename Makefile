main: main.cpp pazymiai.cpp generate.cpp
	g++ main.cpp pazymiai.cpp generate.cpp -o pazymiai

vector:

list:

deque:

clear:
	rm pazymiai


run:
	rm pazymiai
	g++ pazymiai.cpp main.cpp generate.cpp -o pazymiai
	./pazymiai