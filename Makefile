main: pazymiai.cpp helpers.cpp
	g++ pazymiai.cpp helpers.cpp -o pazymiai

clear:
	rm main


run:
	rm pazymiai
	g++ pazymiai.cpp helpers.cpp -o pazymiai
	./pazymiai