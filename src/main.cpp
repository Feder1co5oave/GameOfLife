#include <chrono>
#include <thread>
#include <sched.h>
#include <unistd.h>
#include <vector>
#include "usage.hpp"
#include "Barrier.hpp"
#ifdef GRAPHIC
	#include "MatrixG.hpp"
#endif

using namespace std;

#ifdef GRAPHIC
void bodyThread(MatrixG *m, long start, long end, const gol_run *run, barrier *bar) {
#else
void bodyThread(Matrix *m, long start, long end, const gol_run *run, barrier *bar) {
#endif
	if (!run->configurations) {
		m->randomizeRows(start, end);
		bar->await([&m,run]{
			if (run->check) cout << *m << endl;
		});
	}
	for (long k = 0; k < run->steps; k++) {
		m->updateRows(start, end);
		bar->await([&m]{
			m->swap();
			#ifdef GRAPHIC
			m->print();
			#endif
		});
	}
}

int main(int argc, char *argv[]) {
	const int NPROCS = sysconf(_SC_NPROCESSORS_ONLN);

	if (existArgument(argc, argv, "--help") || existArgument(argc, argv, "-?")) {
		show_usage(argv);
		return 0;
	}

	const gol_run run = parse_arguments(argc, argv, NPROCS);

	#if GRAPHIC
	MatrixG m(run.height, run.width, false);
	#else
	Matrix m(run.height, run.width, false);
	#endif
	
	m.drawConfigurations(run.configurations);

	int nRow = (run.height / run.workers);
	vector<unique_ptr<thread> > tid;
	barrier bar(run.workers);
	cpu_set_t *cpuset = CPU_ALLOC(NPROCS);
	size_t setsize = CPU_ALLOC_SIZE(NPROCS);

	for (long i = 0; i < run.workers; i++) {
		long start = nRow * i;
		long end   = i != run.workers - 1 ? start + nRow : run.height;

		auto th = unique_ptr<thread>(new thread(bodyThread, &m, start, end, &run, &bar));

		#ifdef SETAFFINITY
		#ifdef __MIC__ // bind to different physical cores first
		int cpu = (i*4 + 1 + (i*4)/NPROCS ) % NPROCS;
		#else
		int cpu = i % NPROCS;
		#endif
		CPU_ZERO_S(setsize, cpuset);
		CPU_SET_S(cpu, setsize, cpuset);
		pthread_setaffinity_np(th->native_handle(), setsize, cpuset);
		#endif

		tid.push_back(move(th));
	}

	for (long i = 0; i < run.workers; i++) tid[i]->join();
	CPU_FREE(cpuset);

	if (run.check) cout << m << endl;
	return 0;
}
