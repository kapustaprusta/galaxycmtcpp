#ifndef GALAXYCMT_DIR_WALKER_H
#define GALAXYCMT_DIR_WALKER_H

#include <queue>
#include <mutex>

#include "../walker.h"

namespace galaxycmt {

class DirWalker : public IWalker {
public:
	explicit DirWalker(const WalkerConfig& config = WalkerConfig());
	virtual ~DirWalker() = default;

	void Walk(const std::string& pathToDir) override;

	size_t GetVisitedLength() override;
	std::list<std::string> GetVisited() override;

private:
	std::mutex visitedFilesMutex_;

	std::queue<std::string> dirsToVisit_;

	std::list<std::string> visitedFiles_;
};

} // galaxycmt

#endif //GALAXYCMT_DIR_WALKER_H
