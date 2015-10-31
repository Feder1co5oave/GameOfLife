#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include "Matrix.hpp"

int main(int argc, char *argv[]) {
  // number of threads to be used
  // int nw = std::atoi(argv[1]);
  int h     = 800;
  int w     = 600;
  Matrix *m = new Matrix(h, w);
  m->printG();


  // m->set(-23,40,100);
  std::cout << m->get(-1,0)<<std::endl;
  m->printG();
  for (int i = 0; i < 1000; i++) {
    m->forEach([&](int i, int j, short *v, int alive, int death) {
      // std::cout << i << j << *v << alive << std::endl;
      if (*v == 1) {
        if (alive < 2) *v = 0;

        if (alive > 3) *v = 0;
      }else if (*v == 0) {
        if (alive == 3) *v = 1;
      }
    });
    m->printG();
    // std::cout << "iteration " << i << std::endl;
  }

  return 0;
}
