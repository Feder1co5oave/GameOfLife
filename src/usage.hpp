#include <algorithm>
#include <iostream>
#include <functional>
#include <cassert>
#include "Matrix.hpp"

struct gol_run {
	long height, width, steps, workers, configurations;
	bool check;
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
	std::cout << "Usage: " << argv[0] << " [<params>]\nWhere <params> are:" << std::endl ;
	std::cout << "  --thread | -t <number>  number of threads" << std::endl;
	std::cout << "  --height | -h <number>  height of the matrix" << std::endl;
	std::cout << "  --width  | -w <number>  width of the matrix" << std::endl;
	std::cout << "  --step   | -s <number>  number of step, if 0 run forever" << std::endl;
	std::cout << "  --check  | -c           print hashcodes" << std::endl;
	std::cout << "  --bottles               draw some Bottles" << std::endl;
	std::cout << "  --engines               draw some Schick's Engines" << std::endl;
	std::cout << "  --gliders               draw some Gliders" << std::endl;
	std::cout << "  --guns                  draw some Gosper's Guns" << std::endl;
	std::cout << "  --blobs                 draw some Blobs" << std::endl;
	std::cout << "  --heads                 draw some Hammerheads" << std::endl;
	std::cout << "  --help   | -?           print this help" << std::endl;
	std::cout << "If no configurations are drawn, the World will be initialized at random." << std::endl;
}

gol_run parse_arguments(int argc, char **argv, const long NCPUS) {
	gol_run run = {1000, 1000, 1000, NCPUS, 0, false};

	if (argc <= 1) {
		show_usage(argv);
		exit(EXIT_FAILURE);
	}

	char *arg;

	arg = getArgument(argc, argv, "height");
	if (arg) run.height = std::atoi(arg);
	arg = getArgument(argc, argv, "width");
	if (arg) run.width = std::atoi(arg);
	arg = getArgument(argc, argv, "step");
	if (arg) run.steps = std::atoi(arg);
	arg = getArgument(argc, argv, "thread");
	if (arg) run.workers = std::atoi(arg);
	if (existArgument(argc, argv, "--bottles")) run.configurations |= Matrix::BOTTLE;
	if (existArgument(argc, argv, "--engines")) run.configurations |= Matrix::SCHICKENGINE;
	if (existArgument(argc, argv, "--gliders")) run.configurations |= Matrix::GLIDER;
	if (existArgument(argc, argv, "--guns"))    run.configurations |= Matrix::GOSPERSGUN;
	if (existArgument(argc, argv, "--heads"))   run.configurations |= Matrix::HAMMERHEAD;
	if (existArgument(argc, argv, "--blobs"))   run.configurations |= Matrix::BLOB;
	if (existArgument(argc, argv, "--check")
	 || existArgument(argc, argv, "-c"))        run.check = true;

	assert(run.height > 0);
	assert(run.width > 0);
	assert(run.steps >= 0);
	assert(run.workers > 0);

	return run;
}
