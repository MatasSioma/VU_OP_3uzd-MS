# Define variables
SOURCES = main.cpp helpers.cpp StudentaiClass.cpp

#default
main: $(SOURCES)
	g++ $(SOURCES) -o pazymiai

clean:
	rm -f pazymiai
	rm -f -r sugeneruoti/*geri.txt
	rm -f -r sugeneruoti/*blogi.txt

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
