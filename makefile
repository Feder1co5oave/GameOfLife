OPENCV = `pkg-config --cflags --libs opencv`
CXX = g++
CXXFLAGS = -std=c++11 -pthread -O3

.PHONY: all_build build clean

all_build: build main.out main.x.out

main.out: main.cpp build/Matrix.o build/Barrier.o
	$(CXX) $^ $(CXXFLAGS) -o $@

main.x.out: main.cpp build/Matrix.o build/MatrixG.o build/Barrier.o
	$(CXX) $^ $(CXXFLAGS) $(OPENCV) -DGRAPHIC -o $@

build/%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build/MatrixG.o: MatrixG.cpp MatrixG.hpp
	$(CXX) $(CXXFLAGS) $(OPENCV) -c -o $@ $<

build:
	mkdir -p build

clean:
	rm -Rvf build main.out
