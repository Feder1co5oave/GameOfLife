OPENCV = `pkg-config --cflags --libs opencv`
FF_ROOT = /home/federico/SPM/fastflow
FASTFLOW = -I$(FF_ROOT)
CXX = g++
CXXFLAGS = -std=c++11 -pthread -O3

.PHONY: all build clean

all: build main.out main.x.out main.ff.out

main.out: main.cpp build/Matrix.o build/Barrier.o
	$(CXX) $^ $(CXXFLAGS) -DSETAFFINITY -o $@

main.x.out: main.cpp build/Matrix.o build/MatrixG.o build/Barrier.o
	$(CXX) $^ $(CXXFLAGS) $(OPENCV) -DGRAPHIC -o $@

main.ff.out: main_ff.cpp build/Matrix.o
	$(CXX) $^ $(CXXFLAGS) $(FASTFLOW) -o $@

build/%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build/MatrixG.o: MatrixG.cpp MatrixG.hpp
	$(CXX) $(CXXFLAGS) $(OPENCV) -c -o $@ $<

build:
	mkdir -p build

clean:
	rm -Rvf build main.out
