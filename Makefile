main: main.cpp pazymiai.cpp
	g++ main.cpp pazymiai.cpp -o pazymiai

clear:
	rm pazymiai


run:
	rm pazymiai
	g++ pazymiai.cpp main.cpp -o pazymiai
	./pazymiai