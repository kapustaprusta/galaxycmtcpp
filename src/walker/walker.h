#ifndef GALAXYCMT_WALKER_H
#define GALAXYCMT_WALKER_H

#include <set>
#include <string>

namespace galaxycmt
{

struct WalkerConfig
{
	bool isRecursive{false};
	std::string pathToDir{"./"};
	std::set<std::string> extensions{"h", "hpp", "cpp"};
};

class IWalker
{
public:
	explicit IWalker(const WalkerConfig& config)
		: config_(config){}
	~IWalker() = default;

	virtual bool Walk() = 0;
	virtual bool Walk(const std::string& pathToDir) = 0;

protected:
	WalkerConfig config_;
};

} // galaxycmt

#endif //GALAXYCMT_WALKER_H
