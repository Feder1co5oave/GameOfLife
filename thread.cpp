#include <iostream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <vector>
#include "Matrix.hpp"
//#include "MatrixG.hpp"

char* getArgument(int argc, char **argv, const std::string& option){
  char **end = argv+argc;
  char **itOp = std::find(argv,end,option);
  if (itOp!=end && ++itOp!=end)
    return *itOp;
  else
    return 0;
}

bool existArgument(int argc, char **argv, const std::string& option){
  char **end = argv+argc;
  return std::find(argv,end,option) != end;
}

int main(int argc, char *argv[]) {

  if (existArgument(argc, argv,"--help") ||
      existArgument(argc, argv,"-h")){
    std::cout << "--thread <number> \t number of threads" << std::endl;
    std::cout << "--height <number> \t height of the matrix" << std::endl;
    std::cout << "--width <number> \t width of the matrix" << std::endl;
    std::cout << "--step <number> \t number of step" << std::endl;
    std::cout << "--graphic \t\t activate the graphic mode" << std::endl;
    std::cout << "--help or -h \t\t this help" << std::endl;
    return 0;
  }

  char *nwStr = getArgument(argc,argv,"--thread");
  int nw = nwStr ? std::atoi(nwStr) : std::thread::hardware_concurrency();
  if (nw == 0) nw = 1;

  char *hStr = getArgument(argc,argv, "--height");
  int h     = hStr ? std::atoi(hStr) : 1000;

  char *wStr = getArgument(argc,argv, "--width");
  int w     = wStr ? std::atoi(wStr) : 800;

  char *sStr = getArgument(argc,argv, "--step");
  int s     = sStr ? std::atoi(sStr) : 100;

  //Matrix *m = existArgument(argc, argv,"--graphic") ? new MatrixG(h, w): new Matrix(h,w);

  Matrix *m = new Matrix(h,w);

  int nRow = (h / nw);
  for (int k = 0; k < s; k++) {
    std::vector<std::thread> tid;
    std::cout << "step " << k << std::endl;

    for (int i = 0; i < nw; i++) {
      int start = nRow * i;
      int end   = i!=nw-1 ? start + nRow : h;
      std::cout << "thread" << i << " start: " << start << " end:" << end << std::endl;

      tid.push_back(std::thread([&](Matrix *m, int start, int end)->void {
        m->forEach(start, end, [&](int i, int j, short v, int alive) -> short {
          if (v == 1) {
            if (alive < 2) return 0;

            if (alive > 3) return 0;
          } else if (v == 0) {
            if (alive == 3) return 1;
          }
          return v;
        });
      }, m, start, end));
    }

    for (int i = 0; i < nw; i++) tid[i].join();

    m->swap();
    m->print();
  }
  delete m;
  return 0;
}
