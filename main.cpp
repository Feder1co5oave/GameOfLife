#include <iostream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include "Matrix.hpp"
#include "Barrier.hpp"
#if !NO_OPENCV
  # include "MatrixG.hpp"
#endif // if NO_OPENCV

char* getArgument(int argc, char **argv, const std::string& option) {
  char **end  = argv + argc;
  char **itOp = std::find(argv, end, option);

  if ((itOp != end) && (++itOp != end)) return *itOp;
  else return 0;
}

bool existArgument(int argc, char **argv, const std::string& option) {
  char **end = argv + argc;

  return std::find(argv, end, option) != end;
}

short lifeLogic(int i, int j, short v, int alive) {
  if (v == 1) {
    if (alive < 2) return 0;

    if (alive > 3) return 0;
  } else if (v == 0) {
    if (alive == 3) return 1;
  }
  return v;
}

void bodyThread(Matrix *m, int start, int end, int iterations, barrier *bar) {
  for (int k = 0; k < iterations; k++) {
    m->forEach(start, end, lifeLogic);
    bar->await([&] {
      m->swap();
      // m->print();
      // cout << "step " << k << endl;
    });
  }
}

void bodySequential(Matrix *m, int iterations) {
  for (int k = 0; k < iterations; k++) {
    m->forEach(lifeLogic);
  }
}

int main(int argc, char *argv[]) {
  if (existArgument(argc, argv, "--help") ||
      existArgument(argc, argv, "-h")) {
    std::cout <<
      "--thread <number> \t number of threads, if 0 run the sequential version" <<
      std::endl;
    std::cout << "--height <number> \t height of the matrix" << std::endl;
    std::cout << "--width <number> \t width of the matrix" << std::endl;
    std::cout << "--step <number> \t number of step, if 0 run forever" <<
      std::endl;
    #if !NO_OPENCV
    std::cout << "--graphic \t\t activate the graphic mode" << std::endl;
    #endif // if !NO_OPENCV
    std::cout << "--help or -h \t\t this help" << std::endl;
    return 0;
  }

  char *nwStr = getArgument(argc, argv, "--thread");
  int   nw    = nwStr ? std::atoi(nwStr) : std::thread::hardware_concurrency();

  char *hStr = getArgument(argc, argv, "--height");
  int   h    = hStr ? std::atoi(hStr) : 1000;

  char *wStr = getArgument(argc, argv, "--width");
  int   w    = wStr ? std::atoi(wStr) : 1000;

  char *sStr = getArgument(argc, argv, "--step");
  int   s    = sStr ? std::atoi(sStr) : 1000;

  Matrix *m;
  #if !NO_OPENCV
  m = (existArgument(argc, argv, "--graphic")) ?
      new MatrixG(h, w) :
      new Matrix(h, w);
  #else // if NO_OPENCV
  m = new Matrix(h, w);
  #endif // if NO_OPENCV

  if (nw != 0) {
    int nRow = (h / nw);
    std::vector<std::thread> tid;
    barrier bar(nw);

    for (int i = 0; i < nw; i++) {
      int start = nRow * i;
      int end   = i != nw - 1 ? start + nRow : h;

      // std::cout << "thread" << i << " start: " << start << " end:" << end <<
      // std::endl;

      tid.push_back(std::thread(bodyThread, m, start, end, s, &bar));
    }

    for (int i = 0; i < nw; i++) tid[i].join();
  } else {
    bodySequential(m, s);
  }

  delete m;
  return 0;
}
