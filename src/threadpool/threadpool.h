#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <functional>
#include <condition_variable>

namespace threadpool {

class ThreadPool {
public:
	explicit ThreadPool();
	explicit ThreadPool(uint32_t threads_number);
	~ThreadPool();

	void InitThreads(uint32_t threads_number);
	void Schedule(const std::function<void()>& task);
	void Shutdown();

private:
	std::mutex wait_mutex_;
	std::mutex tasks_mutex_;
	std::atomic_bool is_stop_;
	std::atomic_uint32_t tasks_counter_;
	std::condition_variable condition_variable_;

	std::vector<std::thread> workers_;
	std::queue<std::function<void()>> tasks_;
};

} // namespace threadpool

#endif //THREADPOOL_H
