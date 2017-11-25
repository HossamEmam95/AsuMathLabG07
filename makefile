matrix: main.o matrix.o
	g++ main.o matrix.o -o matrix
	./matrix
main.o:
	g++ -c main.cpp
matrix.o:
	g++ -c matrix.cpp
clean:
	rm *.o matrix
