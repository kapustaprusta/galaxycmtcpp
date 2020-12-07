#include "threadpool.h"

namespace threadpool {

ThreadPool::ThreadPool() {
	is_stop_.store(false);
	tasks_counter_.store(0);

	InitThreads(std::thread::hardware_concurrency());
}

ThreadPool::ThreadPool(const uint32_t threads_number) {
	if (threads_number > std::thread::hardware_concurrency()) {
		throw std::runtime_error("threads number is more than hardware supported");
	}

	is_stop_.store(false);
	tasks_counter_.store(0);

	InitThreads(threads_number);
}

ThreadPool::~ThreadPool() {
	Shutdown();
}

void ThreadPool::InitThreads(const uint32_t threads_number) {
	for (uint32_t thread_idx = 0; thread_idx < threads_number; thread_idx++) {
		workers_.emplace_back([this]() ->void {
			while (true) {
				std::unique_lock<std::mutex> wait_locker(wait_mutex_);
				condition_variable_.wait(wait_locker, [this]() -> bool {
					return !tasks_.empty() || is_stop_.load();
				});
				wait_locker.unlock();

				std::function<void()> my_task;
				{
					std::unique_lock<std::mutex> tasks_locker(tasks_mutex_);
					if (is_stop_.load() && tasks_.empty()) {
						return;
					}

					my_task = std::move(tasks_.front());
					tasks_.pop();
				}
				my_task();
				tasks_counter_--;
			}
		});
	}
}

void ThreadPool::Schedule(const std::function<void()>& task) {
	{
		std::unique_lock<std::mutex> tasks_locker(tasks_mutex_);
		tasks_.push(task);
	}

	tasks_counter_++;
	condition_variable_.notify_one();
}

void ThreadPool::Shutdown() {
	is_stop_.store(true);
	condition_variable_.notify_all();

	for (auto& worker : workers_) {
		if (worker.joinable()) {
			worker.join();
		}
		else {
			worker.detach();
		}
	}

	workers_.clear();
}

} // threadpool

