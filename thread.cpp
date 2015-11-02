#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include "Matrix.hpp"

void bodyThread(Matrix *m, int start, int end) {
  m->forEach(start, end, [&](int i, int j, short v, int alive) -> short {
    // std::cout << i << j << *v << alive << std::endl;
    if (v == 1) {
      if (alive < 2) return 0;

      if (alive > 3) return 0;
    } else if (v == 0) {
      if (alive == 3) return 1;
    }
    return v;
  });
}

int main(int argc, char *argv[]) {
  // number of threads to be used
  int nw    = std::atoi(argv[1]);
  int h     = 1000;
  int w     = 800;
  Matrix *m = new Matrix(h, w, true);

  int nRow = (h / nw);

  for (int i = 0; i < 200; i++) {
    std::vector<std::thread> tid;

    for (int i = 0; i < nw; i++) {
      int start = nRow * i;
      int end   = start + nRow;

      // std::cout << "start:" << start << " " << "end:" << end<<std::endl;
      tid.push_back(std::thread(bodyThread, m, start, end));
    }

    for (int i = 0; i < nw; i++) tid[i].join();

    m->swap();
    m->printG();
  }
  delete m;
  return 0;
}
