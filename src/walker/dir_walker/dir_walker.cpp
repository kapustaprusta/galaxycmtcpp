#include "dir_walker.h"

namespace walker {

DirWalker::DirWalker(const Settings& settings)
	: IWalker(settings)
	, observer_(nullptr)
{

}

bool DirWalker::Walk(const std::string& dir_path) {
	boost::system::error_code errCode;
	if (!boost::filesystem::exists(dir_path, errCode)) {
		throw std::runtime_error(errCode.message());
	}

	if (settings_.is_recursive_) {
		boost::filesystem::recursive_directory_iterator dir_last_node;
		boost::filesystem::recursive_directory_iterator dir_node(dir_path);

		for (; dir_node != dir_last_node; dir_node++) {
			boost::filesystem::path dir_node_path = dir_node->path();
			if (boost::filesystem::is_regular_file(dir_node_path)
			&& settings_.extensions_.empty()
			|| settings_.extensions_.find(dir_node_path.extension().string()) != settings_.extensions_.end()) {
				Notify(dir_node_path.string());
			}
			else if (settings_.skipped_dirs_.find(dir_node_path.string()) != settings_.skipped_dirs_.end()) {
				dir_node.disable_recursion_pending();
			}
		}
	}
	else {
		boost::filesystem::directory_iterator dirLastNode;
		boost::filesystem::directory_iterator dirNode(dir_path);

		for (; dirNode != dirLastNode; dirNode++) {
			boost::filesystem::path dirNodePath = dirNode->path();
			if (boost::filesystem::is_regular_file(dirNodePath)
			&& settings_.extensions_.empty()
			|| settings_.extensions_.find(dirNodePath.extension().string()) != settings_.extensions_.end()) {
				Notify(dirNodePath.string());
			}
		}
	}

	return true;
}

void DirWalker::Notify(const std::string& file_path) {
	std::lock_guard lockGuard(observer_mutex_);
	if (!observer_) {
		return;
	}


}

void DirWalker::Subscribe(ISubcriber* observer) {
	std::lock_guard lockGuard(observer_mutex_);
	if (!observer_) {
		observer_ = observer;
	}
}

void DirWalker::Unsubscribe(ISubcriber* observer) {
	std::lock_guard lockGuard(observer_mutex_);
	observer_ = nullptr;
}

} // namespace walker
