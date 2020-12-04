#ifndef WALKER_H
#define WALKER_H

#include <set>
#include <string>

namespace walker {

struct Settings {
	explicit Settings(bool isRecursive = false,
		              const std::set<std::string>& extensions = {})
		: isRecursive_(false)
		, extensions_(extensions){}
	~Settings() = default;

	bool isRecursive_;
	std::set<std::string> extensions_;
};

class IWalker {
public:
	explicit IWalker(const Settings& settings)
		: settings_(settings){}
	virtual ~IWalker() = default;

	virtual bool Walk(const std::string& dirPath) = 0;

	virtual void SetRecursive(bool isRecursive) {
		settings_.isRecursive_ = isRecursive;
	}

	virtual bool Recursive() const {
		return settings_.isRecursive_;
	}

	virtual void SetExtensions(const std::set<std::string>& extensions) {
		settings_.extensions_ = extensions;
	}

	virtual std::set<std::string> Extensions() const {
		return settings_.extensions_;
	}

protected:
	Settings settings_;
};

} // namespace walker

#endif // WALKER_H
