#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class barrier {

private:
	const int N_THREADS;
	int counts[2];
	int current;
	mutex lock;
	condition_variable condition;
	
	barrier(barrier const&) = delete;
	barrier& operator= (barrier const&) = delete;

public:
	explicit barrier(int n) :
		N_THREADS(n),
		counts {0, 0},
		current(0),
		lock(),
		condition() { }

	/*
	 * Suspend the current thread until all thread have arrived at the barrier.
	 * The thread that has come last executes cb() before awakening all other threads.
	 * @returns true if it is the last thread, false otherwise
	 */
	bool await(function<void()> cb = []{}) {
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
};
