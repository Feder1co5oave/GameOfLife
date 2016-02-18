#include <algorithm>
#include <iostream>
#include <functional>

struct gol_run {
  long height, width, steps, workers;
};

char* getArgument(int argc, char **argv, const std::string& option) {
  char **end  = argv + argc;
  char **itOp = std::find(argv, end, std::string("--") + option);

  if ((itOp != end) && (++itOp != end)) return *itOp;
  else {
    itOp = std::find(argv, end, std::string("-") + option[0]);
    if ((itOp != end) && (++itOp != end)) return *itOp;
    else return 0;
  }
}

bool existArgument(int argc, char **argv, const std::string& option) {
  char **end = argv + argc;

  return std::find(argv, end, option) != end;
}

void show_usage() {
  std::cout << "--thread | -t <number>  number of threads, if 0 run the sequential version" << std::endl;
  std::cout << "--height | -h <number>  height of the matrix" << std::endl;
  std::cout << "--width  | -w <number>  width of the matrix" << std::endl;
  std::cout << "--step   | -s <number>  number of step, if 0 run forever" << std::endl;
  std::cout << "--help or -h \t\t this help" << std::endl;
}

gol_run parse_arguments(int argc, char **argv, const long NCPUS) {
  gol_run run = {1000, 1000, 1000, NCPUS};
  
  #ifdef EXTREME_TEST
  
  run.height  = std::atoi(argv[1]);
  run.width   = std::atoi(argv[1]);
  run.steps   = std::atoi(argv[2]);
  run.workers = std::atoi(argv[3]);
  
  #else

  char *arg;

  arg = getArgument(argc, argv, "thread");
  if (arg) run.workers = std::atoi(arg);
  arg = getArgument(argc, argv, "height");
  if (arg) run.height = std::atoi(arg);
  arg = getArgument(argc, argv, "width");
  if (arg) run.width = std::atoi(arg);
  arg = getArgument(argc, argv, "step");
  if (arg) run.steps = std::atoi(arg);

  #endif

  return run;
}