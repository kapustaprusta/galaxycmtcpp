#ifndef GALAXYCMT_DIR_WALKER_H
#define GALAXYCMT_DIR_WALKER_H

#include "../walker.h"

namespace galaxycmt
{

class DirWalker : public IWalker
{
public:
	explicit DirWalker(const WalkerConfig& config)
		: IWalker(config){}
	virtual ~DirWalker() = default;

	bool Walk() override;
	bool Walk(const std::string& pathToDir) override;
};

} // galaxycmt

#endif //GALAXYCMT_DIR_WALKER_H
