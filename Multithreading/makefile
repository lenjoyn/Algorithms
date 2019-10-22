all: TestThread TestThread.o

TestThread.o: TestThread2.cxx 
	g++ -c TestThread2.cxx -o TestThread.o

TestThread: TestThread.o
	g++ TestThread.o -o TestThread -I .

clean:
	rm TestThread.o TestThread
