all: PuzzleSolver PuzzleSolver.o

PuzzleSolver.o: PuzzleSolver.cxx 
	g++ -c PuzzleSolver.cxx -o PuzzleSolver.o

PuzzleSolver: PuzzleSolver.o
	g++ PuzzleSolver.o -o PuzzleSolver -I .

clean:
	rm PuzzleSolver.o PuzzleSolver
