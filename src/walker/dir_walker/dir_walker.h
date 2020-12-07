#ifndef DIR_WALKER_H
#define DIR_WALKER_H

#include <iostream>

#include <queue>
#include <mutex>
#include <string>
#include <boost/lockfree/spsc_queue.hpp>

#include "../walker.h"

namespace walker {

typedef boost::lockfree::spsc_queue<std::string, boost::lockfree::fixed_sized<true>> string_queue;

class DirWalker final : public IWalker,
                        public IPublisher {
public:
	explicit DirWalker(const Settings& settings = Settings{});
	~DirWalker() final = default;

	bool Walk(const std::string& dir_path) override;

	void Subscribe(ISubcriber* observer) override;
	void Unsubscribe(ISubcriber* observer) override;
	void Notify(const std::string& file_path) override;

private:
	ISubcriber* observer_;

	std::mutex observer_mutex_;
};

} // namespace walker

#endif // DIR_WALKER_H
