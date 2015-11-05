#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include "Matrix.hpp"

int main(int argc, char *argv[]) {
  // number of threads to be used
  // int nw = std::atoi(argv[1]);
  int h     = 1000;
  int w     = 800;
  Matrix *m = new Matrix(h, w);

  m->print();

  for (int i = 0; i < 200; i++) {
    m->forEach([&](int i, int j, short v, int alive) -> short {
      if (v == 1) {
        if (alive < 2) return 0;

        if (alive > 3) return 0;
      } else if (v == 0) {
        if (alive == 3) return 1;
      }
      return v;
    });
    m->swap();
    m->print();
  }
  delete m;
  return 0;
}
