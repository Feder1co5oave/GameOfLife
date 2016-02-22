#include "usage.hpp"

using namespace std;

void bodySequential(Matrix& m, gol_run& run) {
	for (long k = 0; k < run.steps; k++) {
		m.updateRows(0, run.height);
		m.swap();
		//m->print();
	}
}

int main(int argc, char *argv[]) {
	if (existArgument(argc, argv, "--help") || existArgument(argc, argv, "-?")) {
		show_usage(argv);
		return 0;
	}

	gol_run run = parse_arguments(argc, argv, 0);
	Matrix m(run.height, run.width, true);
	
	bodySequential(m, run);
	
	return 0;
}
