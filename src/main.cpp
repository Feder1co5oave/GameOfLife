#include <chrono>
#include <thread>
#include <sched.h>
#include <unistd.h>
#include <vector>
#include "usage.hpp"
#include "Barrier_atomic.hpp"
#include "nb_queue.hpp"
#ifdef GRAPHIC
	#include "MatrixG.hpp"
#endif

#define CHUNK_SIZE 200

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

using namespace std;

#ifdef GRAPHIC
void bodyThread(MatrixG *m, const gol_run *run, barrier *bar, nb_queue<long,long> *q) {
#else
void bodyThread(Matrix *m, const gol_run *run, barrier *bar, nb_queue<pair<long,long>> *q) {
#endif
	if (!run->configurations) {
		const pair<long,long> *next;
		while (next = q->get()) m->randomizeRows(next->first, next->second);
		bar->await([m,q,run]{
			q->reset();
			if (run->check) cout << *m << endl;
		});
	}
	for (long k = 0; k < run->steps; k++) {
		const pair<long,long> *next;
		while (next = q->get()) m->updateRows(next->first, next->second);
		bar->await([m,q]{
			q->reset();
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

	long nChunks = run.workers * 20;
	long chunk_size = run.height / nChunks;
	pair<long,long> *chunks = new pair<long,long>[nChunks];
	for (long i = 0; i < nChunks; i++) chunks[i] = make_pair(i * chunk_size, MIN((i+1) * chunk_size, run.height));

	vector<unique_ptr<thread> > tid;
	barrier bar(run.workers);
	nb_queue<pair<long,long>> queue(nChunks, chunks);
	cpu_set_t *cpuset = CPU_ALLOC(NPROCS);
	size_t setsize = CPU_ALLOC_SIZE(NPROCS);

	for (long i = 0; i < run.workers; i++) {
		auto th = unique_ptr<thread>(new thread(bodyThread, &m, &run, &bar, &queue));

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
