#include "Barrier.hpp"

barrier::barrier(int n) :
	N_THREADS(n),
	counts {0, 0},
	current(0),
	lock(),
	condition()
	{ }

bool barrier::await(function<void()> cb) {
	unique_lock<mutex> _lock(lock);
	int my = current;
	counts[my]++;

	if (counts[my] < N_THREADS) {
		condition.wait(_lock, [&]{ return counts[my] == N_THREADS; });
		return false;
	} else {
		current ^= 1;
		counts[current] = 0;
		if (cb) cb();
		condition.notify_all();
		return true;
	}
}
