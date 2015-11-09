all_build: build main.out

main.out: main.cpp build/Matrix.o build/MatrixG.o
	g++ main.cpp build/MatrixG.o build/Matrix.o \
			-std=c++11 \
			-pthread \
			`pkg-config --cflags --libs opencv` \
			-g \
			-o main.out

build/MatrixG.o: MatrixG.cpp
	g++ MatrixG.cpp \
			-g \
			-c \
			-std=c++11 \
			`pkg-config --cflags --libs opencv` \
			-o build/MatrixG.o

build/Matrix.o: Matrix.cpp
		g++ Matrix.cpp \
				-g \
				-c \
				-std=c++11 \
				-o build/Matrix.o

build:
	mkdir -p build