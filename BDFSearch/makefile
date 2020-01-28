all:test test.o
test.o:test.cxx
	g++ -c test.cxx -o test.o
test:test.o
	g++ test.o -o test -I .
clean:
	rm test test.o
