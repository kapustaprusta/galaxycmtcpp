#include <boost/filesystem.hpp>

#include "dir_walker.h"

namespace galaxycmt
{

DirWalker::DirWalker(const WalkerConfig& config)
	: IWalker(config)
{

}

void DirWalker::Walk(const std::string& pathToDir)
{
	dirsToVisit_.push(pathToDir);
	while (!dirsToVisit_.empty())
	{
		std::string pathToCurrDir = dirsToVisit_.front();
		dirsToVisit_.pop();

		boost::filesystem::directory_iterator dirNode(pathToCurrDir);
		boost::filesystem::directory_iterator dirNodesEnd;

		for (; dirNode != dirNodesEnd; dirNode++)
		{
			boost::filesystem::file_status fileStatus = boost::filesystem::status(*dirNode);
			if (fileStatus.type() == boost::filesystem::regular_file)
			{
				std::lock_guard lockGuard(visitedFilesMutex_);
				visitedFiles_.push_back(dirNode->path().string());
			}
			else if (config_.isRecursive_
				  && fileStatus.type() == boost::filesystem::directory_file)
			{
				// should visit directory if it not set as a skipped
				if (!config_.skippedPaths_.count(dirNode->path().string()))
				{
					dirsToVisit_.push(dirNode->path().string());
				}
			}
		}
	}
}

std::list<std::string> DirWalker::GetVisited()
{
	std::lock_guard lockGuard(visitedFilesMutex_);
	auto tmpVisitedFiles = std::list<std::string>{visitedFiles_.begin(),
												  visitedFiles_.end()};
	visitedFiles_.clear();

	return tmpVisitedFiles;
}

} // galaxycmt
