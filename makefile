all_build: build s.out t.out test.out

s.out: sequential.cpp build/Matrix.o
	g++ -g -std=c++11 sequential.cpp build/Matrix.o -o s.out

t.out: thread.cpp build/Matrix.o build/MatrixG.o
	g++ -g thread.cpp build/MatrixG.o build/Matrix.o -std=c++11 -pthread `pkg-config --cflags --libs opencv` -o t.out

test.out: test.cpp build/MatrixG.o build/Matrix.o
	g++ -g test.cpp build/MatrixG.o build/Matrix.o -std=c++11 -pthread `pkg-config --cflags --libs opencv` -o test.out

build/MatrixG.o: MatrixG.cpp
	g++ -g -c -std=c++11 `pkg-config --cflags --libs opencv` MatrixG.cpp -o build/MatrixG.o

build/Matrix.o: Matrix.cpp
		g++ -g -c -std=c++11 Matrix.cpp -o build/Matrix.o

build:
	mkdir -p build
