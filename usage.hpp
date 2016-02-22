#include <algorithm>
#include <iostream>
#include <functional>
#include <cassert>

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

void show_usage(char **argv) {
	#ifdef EXTREME_TEST
	std::cout << "Usage: " << argv[0] << " <size> <steps> <threads>" << std::endl;
	#else
	std::cout << "Usage: " << argv[0] << " [<params>]\nWhere <params> are:" << std::endl ;
	std::cout << "  --thread | -t <number>  number of threads, if 0 run the sequential version" << std::endl;
	std::cout << "  --height | -h <number>  height of the matrix" << std::endl;
	std::cout << "  --width  | -w <number>  width of the matrix" << std::endl;
	std::cout << "  --step   | -s <number>  number of step, if 0 run forever" << std::endl;
	std::cout << "  --help   | -?           print this help" << std::endl;
	#endif
}

gol_run parse_arguments(int argc, char **argv, const long NCPUS) {
	gol_run run = {1000, 1000, 1000, NCPUS};
	
	#ifdef EXTREME_TEST
	
	if (argc < 4) {
		show_usage(argv);
		exit(EXIT_FAILURE);
	}

	if (argc > 1) run.height = run.width = std::atoi(argv[1]);
	if (argc > 2) run.steps = std::atoi(argv[2]);
	if (argc > 3) run.workers = std::atoi(argv[3]);
	
	#else

	char *arg;

	arg = getArgument(argc, argv, "height");
	if (arg) run.height = std::atoi(arg);
	arg = getArgument(argc, argv, "width");
	if (arg) run.width = std::atoi(arg);
	arg = getArgument(argc, argv, "step");
	if (arg) run.steps = std::atoi(arg);
	arg = getArgument(argc, argv, "thread");
	if (arg) run.workers = std::atoi(arg);

	#endif

	assert(run.height > 0);
	assert(run.width > 0);
	assert(run.steps >= 0);
	assert(run.workers > 0);

	return run;
}
