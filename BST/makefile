
all: test test.o

test.o: test.cpp
	g++ -c test.cpp -I . -o test.o  -std=c++17

test: test.o
	g++ test.o -o test -I .

clean:
	rm test.o test
