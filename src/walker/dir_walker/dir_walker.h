#ifndef DIR_WALKER_H
#define DIR_WALKER_H

#include <queue>
#include <mutex>
#include <string>

#include "../walker.h"

namespace walker {

class DirWalker : public IWalker,
                  public ISubject {
public:
	explicit DirWalker(const Settings& settings);
	~DirWalker() = default;

	void Notify() override;
	void Subscribe(IObserver* observer) override;
	void Unsubscribe(IObserver* observer) override;

	bool Walk(const std::string& dirPath) override;

private:
	std::mutex filePathsMutex_;

	std::set<IObserver*> observers_;

	std::queue<std::string> filePaths_;
};

} // namespace walker

#endif // DIR_WALKER_H
