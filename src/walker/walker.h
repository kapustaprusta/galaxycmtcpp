#ifndef WALKER_H
#define WALKER_H

#include <set>
#include <string>

namespace walker {

class IObserver;

struct Settings {
	explicit Settings(bool isRecursive = false,
					  const std::set<std::string>& extensions = {})
		: isRecursive_(false)
		, extensions_(extensions){}
	~Settings() = default;

	bool isRecursive_;
	std::set<std::string> extensions_;
};

class ISubject {
public:
	ISubject() = default;
	virtual ~ISubject() = default;

	virtual void Notify() = 0;
	virtual void Subscribe(IObserver* observer) = 0;
	virtual void Unsubscribe(IObserver* observer) = 0;
};

class IWalker {
public:
	explicit IWalker(const Settings& settings)
		: settings_(settings){}
	virtual ~IWalker() = default;

	virtual bool Walk(const std::string& dirPath) = 0;

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
