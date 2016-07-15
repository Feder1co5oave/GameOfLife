#include <atomic>
#include <functional>

using namespace std;

class barrier {
private:
	const int N_THREADS;
	atomic<int> count;
	atomic<int> generation;

	barrier(barrier const&) = delete;
	barrier& operator= (barrier const&) = delete;

public:
	explicit barrier(int n) :
		N_THREADS(n),
		count(0),
		generation(0) { }

	bool await(function<void()> cb = []{}) {
		int my_gen = generation.load();
		if (count.fetch_add(1) == N_THREADS - 1) {
			if (cb) cb();
			count.store(0);
			generation.fetch_add(1);
			return true;
		} else {
			do { } while (my_gen == generation.load());
			return false;
		}
	}

	virtual ~barrier() { }
};
