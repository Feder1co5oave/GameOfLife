#include <atomic>

template <class T>
class nb_queue {
	const size_t size;
	const T* const queue;
	std::atomic<long> next;
public:
	nb_queue(const size_t _size, const T* data): size(_size), queue(data), next(0) { }
	void reset() { next = 0; }
	const T* get() {
		long _next = next++;
		return _next >= size ? nullptr : &queue[_next];
	}
};
