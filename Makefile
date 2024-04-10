# Define variables
SOURCES = main.cpp heleprs.cpp StudentaiClass.cpp generate.cpp

#default
main: $(SOURCES)
	@echo "\033[0;33mĮsitikinkite kad pakeitėte Container aprašą į norimą: "std::vector"/"std::list"/"std::deque", pazymiai.h faile, kaip nurodyta instrukcijoje.\033[0m"  
	g++ $(SOURCES) -o pazymiai

clean:
	rm -f pazymiai
	rm -f -r sugeneruoti/*geri.txt
	rm -f -r sugeneruoti/*blogi.txt

run:
	make clean
	make
	@echo "\n"
	./pazymiai