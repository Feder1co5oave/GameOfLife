build: dir s.out t.out

s.out: sequential.cpp Matrix.o
	g++ -std=c++11 sequential.cpp build/Matrix.o -o s.out

t.out: thread.cpp Matrix.o
	g++ -std=c++11 -pthread thread.cpp build/Matrix.o -o t.out

Matrix.o:
	g++ -c -std=c++11 Matrix.cpp -o build/Matrix.o

dir:
	mkdir -p build
