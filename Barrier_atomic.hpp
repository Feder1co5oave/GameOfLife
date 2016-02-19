#include <atomic>
#include <functional>

using namespace std;

class barrier {
private:
	const int N_THREADS;
	atomic<int> count;
	atomic<int> generation;
	const function<void(int)> new_gen;

	barrier(barrier const&) = delete;
	barrier& operator= (barrier const&) = delete;

public:
	barrier(int n, function<void(int)> ng) :
		N_THREADS(n),
		count(0),
		generation(0),
		new_gen(ng) { }

	explicit barrier(int n) :
		barrier(n, nullptr) { }

	bool await() {
		int my_gen = generation.load();
		if (count.fetch_add(1) == N_THREADS - 1) {
			if (new_gen) new_gen(my_gen);
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