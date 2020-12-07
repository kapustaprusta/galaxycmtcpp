#ifndef WALKER_H
#define WALKER_H

#include <set>
#include <string>
#include <boost/filesystem.hpp>

namespace walker {

class ISubcriber;

struct Settings {
	explicit Settings(bool isRecursive = false,
					  const std::set<std::string>& extensions = {},
					  const std::set<std::string>& skipped_dirs = {})
		: is_recursive_(false)
		, extensions_(extensions)
		, skipped_dirs_(skipped_dirs){}
	~Settings() = default;

	bool is_recursive_;
	std::set<std::string> extensions_;
	std::set<std::string> skipped_dirs_;
};

class IPublisher {
public:
	IPublisher() = default;
	virtual ~IPublisher() = default;

	virtual void Subscribe(ISubcriber* observer) = 0;
	virtual void Unsubscribe(ISubcriber* observer) = 0;
	virtual void Notify(const std::string& file_path) = 0;
};

class IWalker {
public:
	explicit IWalker(const Settings& settings)
		: settings_(settings){}
	virtual ~IWalker() = default;

	virtual bool Walk(const std::string& dir_path) = 0;

	virtual void SetSettings(const Settings& settings) {
		settings_ = settings;
	}

	virtual Settings GetSettings() const {
		return settings_;
	}

protected:
	Settings settings_;
};

} // namespace walker

#endif // WALKER_H
