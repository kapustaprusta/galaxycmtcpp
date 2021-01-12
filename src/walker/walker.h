#ifndef GALAXYCMT_WALKER_H
#define GALAXYCMT_WALKER_H

#include <set>
#include <queue>
#include <string>
#include <boost/filesystem.hpp>

namespace galaxycmt {

struct WalkerConfig {
	WalkerConfig(bool isRecursive = false,
			     const std::set<std::string>& skippedPaths = {},
			     const std::string& pathToRootDir = "./")
		: isRecursive_(isRecursive) {
		for (const auto& skippedPath : skippedPaths) {
			skippedPaths_.insert(boost::filesystem::absolute(skippedPath, pathToRootDir).string());
		}
	}

	bool isRecursive_;
	std::set<std::string> skippedPaths_;
};

class IWalker {
public:
	explicit IWalker(const WalkerConfig& config)
		: config_(config){}
	~IWalker() = default;

	virtual void Walk(const std::string& pathToDir) = 0;

	virtual size_t GetVisitedLength() = 0;
	virtual std::list<std::string> GetVisited() = 0;

protected:
	WalkerConfig config_;
};

} // galaxycmt

#endif //GALAXYCMT_WALKER_H
