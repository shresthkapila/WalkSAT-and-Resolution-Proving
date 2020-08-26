all: propositionalTP.o main.o walksat.o
	g++ -o app propositionalTP.o main.o walksat.o
propositionalTP.o: propositionalTP.cpp propositionalTP.h
	g++ -c propositionalTP.cpp
main.o: main.cpp propositionalTP.h walksat.h
	g++ -c main.cpp
walksat.o: walksat.cpp walksat.h
	g++ -c walksat.cpp
clean:
	rm -f *.o app