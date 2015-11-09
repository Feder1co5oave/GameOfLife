build: dir s.out t.out

s.out: sequential.cpp Matrix.o
	g++ -std=c++11 sequential.cpp build/Matrix.o -o s.out

t.out: thread.cpp Matrix.o MatrixG.o
	g++ -g -std=c++11 -pthread `pkg-config --cflags --libs opencv` thread.cpp build/MatrixG.o build/Matrix.o -o t.out

MatrixG.o:
	g++ -g -c -std=c++11 `pkg-config --cflags --libs opencv` MatrixG.cpp -o build/MatrixG.o

Matrix.o:
		g++ -g -c -std=c++11 Matrix.cpp -o build/Matrix.o

dir:
	mkdir -p build
