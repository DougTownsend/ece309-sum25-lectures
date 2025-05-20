compl: main.o complex.o
	g++ main.o complex.o -o compl

main.o: main.cpp complex.hpp
	g++ -c main.cpp -o main.o

complex.o: complex.cpp complex.hpp
	g++ -c complex.cpp -o complex.o

clean:
	rm *.o compl