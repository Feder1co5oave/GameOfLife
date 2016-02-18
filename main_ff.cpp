#include "usage.hpp"
#include "Matrix.hpp"

#ifdef __MIC__
	#define NO_DEFAULT_MAPPING
#endif
#include <ff/parallel_for.hpp>

int main(int argc, char *argv[]) {
	const int NPROCS = sysconf(_SC_NPROCESSORS_ONLN);

	if (existArgument(argc, argv, "--help") || existArgument(argc, argv, "-h")) {
		show_usage(argv);
		return 0;
	}

	gol_run run = parse_arguments(argc, argv, NPROCS);
	Matrix m(run.height, run.width, true);

	if (run.workers != 0) {
		ff::ParallelFor pf;
		for (long i = 0; i < run.steps; i++) {
			pf.parallel_for_idx(0, run.height, 1, 0,
				[&m](const long start, const long end, const int thid){
					m.updateRows(start, end);
				}, run.workers);
			m.swap();
		}
	} else {
		for (long i = 0; i < run.steps; i++) m.updateRows(0, run.height);
	}
	return 0;
}