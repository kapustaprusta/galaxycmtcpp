#include <boost/filesystem.hpp>

#include "dir_walker.h"

namespace walker {

DirWalker::DirWalker(const Settings& settings)
	: IWalker(settings)
{

}

bool DirWalker::Walk(const std::string& dirPath) {
	if (boost::filesystem::is_directory(dirPath)) {

	} else {

	}

	return false;
}

void DirWalker::Notify() {
	// Notify all observers
}

void DirWalker::Subscribe(IObserver* observer) {
	if (observers_.empty()) {
		observers_.insert(observer);
	}
}

void DirWalker::Unsubscribe(IObserver* observer) {
	observers_.clear();
}

} // namespace walker
