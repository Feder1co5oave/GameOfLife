OPENCV = `pkg-config --cflags --libs opencv`
FF_ROOT = /home/federico/SPM/fastflow
FASTFLOW = -I$(FF_ROOT)
CXX = g++
CXXFLAGS = -std=c++11 -pthread -O3
OPTS = -DEXTREME_TEST

.PHONY: all build clean

all: build main.out main.ff.out main.seq.out

main.out: main.cpp libs/Matrix.o libs/Barrier.o
	$(CXX) $^ $(CXXFLAGS) $(OPTS) -o $@

main.x.out: main.cpp libs/Matrix.o libs/MatrixG.o libs/Barrier.o
	$(CXX) $^ $(CXXFLAGS) $(OPENCV) -DGRAPHIC -o $@

main.ff.out: main_ff.cpp libs/Matrix.o
	$(CXX) $^ $(CXXFLAGS) $(FASTFLOW) $(OPTS) -o $@

main.seq.out: main_seq.cpp libs/Matrix.o
	$(CXX) $^ $(CXXFLAGS) $(OPTS) -o $@

libs/%.o: %.cpp %.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

libs/MatrixG.o: MatrixG.cpp MatrixG.hpp
	$(CXX) $(CXXFLAGS) $(OPENCV) -c -o $@ $<

build:
	mkdir -p libs

clean:
	rm -Rvf libs/* *.out
