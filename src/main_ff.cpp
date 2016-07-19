#include <iostream>
#include "usage.hpp"

#ifdef __MIC__
	#define NO_DEFAULT_MAPPING
#endif
#include <ff/parallel_for.hpp>

using namespace std;

int main(int argc, char *argv[]) {
	const int NPROCS = sysconf(_SC_NPROCESSORS_ONLN);

	if (existArgument(argc, argv, "--help") || existArgument(argc, argv, "-?")) {
		show_usage(argv);
		return 0;
	}

	gol_run run = parse_arguments(argc, argv, NPROCS);
	Matrix m(run.height, run.width, false);

	#ifdef SPIN
	ff::ParallelFor pf(run.workers, true, true);
	#else
	ff::ParallelFor pf(run.workers);
	#endif
	
	pf.parallel_for_idx(0, run.height, 1, 0,
		[&m](const long start, const long end, const int) {
			m.randomizeRows(start, end);
	}, run.workers);

	if (run.check) cout << m << endl;

	for (long i = 0; i < run.steps; i++) {
		pf.parallel_for_idx(0, run.height, 1, 0,
			[&m](const long start, const long end, const int thid) {
				m.updateRows(start, end);
		}, run.workers);
		m.swap();
	}

	if (run.check) cout << m << endl;

	return 0;
}