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
	explicit barrier(int n);
	bool await(function<void()> cb);
	virtual ~barrier() {}
};