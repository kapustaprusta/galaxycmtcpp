#ifndef MANAGER_H
#define MANAGER_H

#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <functional>
#include <condition_variable>

namespace manager {

class ISubscriber {
public:
	ISubscriber() = default;
	virtual ~ISubscriber() = default;

	virtual Update(const std::string& filePath) = 0;
};

class IManager() {
public:
	explicit ThreadPool();
	explicit ThreadPool(uint32_t threads_number);
	virtual ~ThreadPool();

	virtual void InitThreads(uint32_t threads_number) = 0;
	virtual void Schedule(const std::function<void()>& task) = 0;
	virtual void Shutdown() = 0;

private:
	std::mutex wait_mutex_;
	std::mutex tasks_mutex_;
	std::atomic_bool is_stop_;
	std::atomic_uint32_t tasks_counter_;
	std::condition_variable condition_variable_;

	std::vector<std::thread> workers_;
	std::queue<std::function<void()>> tasks_;
};

} // namespace manager

#endif // MANAGER_H
