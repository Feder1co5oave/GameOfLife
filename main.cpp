#include <iostream>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <sched.h>
#include <unistd.h>
#include <vector>
#include <memory>
#include "Matrix.hpp"
#include "Barrier.hpp"
#ifdef GRAPHIC
  #include "MatrixG.hpp"
#endif

using namespace std;

#if !EXTREME_TEST
char* getArgument(int argc, char **argv, const std::string& option) {
  char **end  = argv + argc;
  char **itOp = std::find(argv, end, string("--") + option);

  if ((itOp != end) && (++itOp != end)) return *itOp;
  else {
    itOp = std::find(argv, end, string("-") + option[0]);
    if ((itOp != end) && (++itOp != end)) return *itOp;
    else return 0;
  }
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
  //cout << "thread " << start << " running on cpu " << sched_getcpu() << endl;
  //usleep(rand() % 1000000);
  //cerr << -sched_getcpu();
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
  const int NPROCS = sysconf(_SC_NPROCESSORS_ONLN);

  #if !EXTREME_TEST

  if (existArgument(argc, argv, "--help") ||
      existArgument(argc, argv, "-?")) {
    std::cout <<
      "--thread <number> \t number of threads, if 0 run the sequential version" <<
      std::endl;
    std::cout << "--height <number> \t height of the matrix" << std::endl;
    std::cout << "--width <number> \t width of the matrix" << std::endl;
    std::cout << "--step <number> \t number of step, if 0 run forever" << std::endl;
    std::cout << "--help or -h \t\t this help" << std::endl;
    return 0;
  }


  char *nwStr = getArgument(argc, argv, "thread");
  int   nw    = nwStr ? std::atoi(nwStr) : NPROCS;

  char *hStr = getArgument(argc, argv, "height");
  int   h    = hStr ? std::atoi(hStr) : 1000;

  char *wStr = getArgument(argc, argv, "width");
  int   w    = wStr ? std::atoi(wStr) : 1000;

  char *sStr = getArgument(argc, argv, "step");
  int   s    = sStr ? std::atoi(sStr) : 1000;
  #else // if EXTREME_TEST
  int h  = atoi(argv[1]);
  int w  = atoi(argv[1]);
  int s  = atoi(argv[2]);
  int nw = atoi(argv[3]);
  #endif // if EXTREME_TEST

  #if GRAPHIC && !EXTREME_TEST
  MatrixG m(h, w);
  for (long p = 0; p < w; p += 50)
    //for (long q = 0; q < h-25; q += 40)
      //m.draw(GLIDER, p, q+p);
      m.draw(GOSPERSGUN, p, 20);
  m.swap();
  #else // if !GRAPHIC
  Matrix m(h, w, true);
  #endif

  if (nw != 0) {
    int nRow = (h / nw);
    vector<unique_ptr<thread> > tid;
    barrier bar(nw);
    cpu_set_t *cpuset = CPU_ALLOC(NPROCS);
    size_t setsize = CPU_ALLOC_SIZE(NPROCS);

    for (long i = 0; i < nw; i++) {
      long start = nRow * i;
      long end   = i != nw - 1 ? start + nRow : h;
      int cpu;

      // std::cout << "thread" << i << " start: " << start << " end:" << end << std::endl;
      auto th = unique_ptr<thread>(new thread(bodyThread, &m, start, end, s, &bar));

      #ifdef __MIC__ // bind to different physical cores first
      cpu = (i*4 + 1 + (i*4)/NPROCS ) % NPROCS;
      #else
      cpu = i % NPROCS;
      #endif

      #ifdef SETAFFINITY
      CPU_ZERO_S(setsize, cpuset);
      CPU_SET_S(cpu, setsize, cpuset);
      pthread_setaffinity_np(th->native_handle(), setsize, cpuset);
      //cerr << "bind to cpu#" << cpu << endl;
      #endif

      tid.push_back(move(th));
    }

    for (long i = 0; i < nw; i++) tid[i]->join();

    CPU_FREE(cpuset);
  } else {
    bodySequential(&m, s);
  }

  return 0;
}
