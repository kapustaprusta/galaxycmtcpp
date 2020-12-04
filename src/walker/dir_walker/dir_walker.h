#ifndef DIR_WALKER_H
#define DIR_WALKER_H

#include "../walker.h"

namespace walker {

class DirWalker : public IWalker {
public:
	explicit DirWalker(const Settings& settings)
		: IWalker(settings){}
	~DirWalker() = default;

	bool Walk(const std::string& dirPath) override;
};

} // namespace walker

#endif // DIR_WALKER_H
