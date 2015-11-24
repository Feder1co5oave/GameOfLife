#include <iostream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include "Matrix.hpp"
#include "Barrier.hpp"
#ifdef GRAPHIC
  #include "MatrixG.hpp"
#endif

#if !EXTREME_TEST
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

#endif // if !EXTREME_TEST

#ifdef GRAPHIC
void bodyThread(MatrixG *m, long start, long end, long iterations, barrier *bar) {
#else
void bodyThread(Matrix *m, long start, long end, long iterations, barrier *bar) {
#endif
  for (long k = 0; k < iterations; k++) {
    m->updateRows(start, end);
    bar->await([&]{
      m->swap();

      #ifdef GRAPHIC
      m->print();
      #endif
      // cout << "step " << k << endl;
    });
  }
}

void bodySequential(Matrix *m, long iterations) {
  for (long k = 0; k < iterations; k++) {
    m->forEach([](long i, long j, cell_t cell, long liveNeighbors){
      return Matrix::lifeLogic(cell, liveNeighbors);
    });
    m->print();
  }
}

int main(int argc, char *argv[]) {
  #if !EXTREME_TEST

  if (existArgument(argc, argv, "--help") ||
      existArgument(argc, argv, "-h")) {
    std::cout <<
      "--thread <number> \t number of threads, if 0 run the sequential version" <<
      std::endl;
    std::cout << "--height <number> \t height of the matrix" << std::endl;
    std::cout << "--width <number> \t width of the matrix" << std::endl;
    std::cout << "--step <number> \t number of step, if 0 run forever" << std::endl;
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
  #else // if EXTREME_TEST
  int h  = atoi(argv[1]);
  int w  = atoi(argv[1]);
  int s  = atoi(argv[2]);
  int nw = atoi(argv[3]);
  #endif // if EXTREME_TEST

  #if GRAPHIC && !EXTREME_TEST
  MatrixG m(h, w, true);
  #else // if !GRAPHIC
  Matrix m(h, w, true);
  #endif

  if (nw != 0) {
    int nRow = (h / nw);
    std::vector<std::thread> tid;
    barrier bar(nw);

    for (long i = 0; i < nw; i++) {
      long start = nRow * i;
      long end   = i != nw - 1 ? start + nRow : h;

      // std::cout << "thread" << i << " start: " << start << " end:" << end << std::endl;

      tid.push_back(std::thread(bodyThread, &m, start, end, s, &bar));
    }

    for (long i = 0; i < nw; i++) tid[i].join();
  } else {
    bodySequential(&m, s);
  }

  return 0;
}
