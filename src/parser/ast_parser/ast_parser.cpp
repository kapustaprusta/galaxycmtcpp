#include <atomic>
#include <future>
#include <fstream>

//
#include <iostream>
//

#include "ast_parser.h"
#include "../../walker/walker.h"

namespace galaxycmt
{

ASTParser::ASTParser(const std::shared_ptr<IWalker>& walker)
	: walker_(walker)
{
	filesExtensions_ = {".h",
					    ".hpp",
					    ".cpp"};
}

void ASTParser::Parse(const Node& node) {
	if (node.type_ == NodeType::FILE) {
		ParseFile(node.path_);
	}

	ParseDir(node.path_);
}

void ASTParser::ParseFile(const std::string& pathToFile) {
	std::string parsedFileExtension = pathToFile
								.substr(pathToFile.find_last_of('.'));

	if (filesExtensions_.count(parsedFileExtension))
	{
		std::fstream parsedFile(pathToFile, std::fstream::in);
		if (!parsedFile.is_open())
		{
			// TODO: change on log
			std::cout << "cannot open file: " + pathToFile + "\n";
			return;
		}

		std::string strLine;
		std::getline(parsedFile, strLine);
		std::cout << strLine << "\n";
	}
}

void ASTParser::ParseDir(const std::string& pathToDir) {
	if (!walker_) {
		return;
	}

	// walk
	std::atomic<bool> isStop = false;
	auto walkingFuture = std::async(std::launch::async,
								    [&]() -> void {
										try {
											walker_->Walk(pathToDir);
										}
										catch (std::exception& e) {
											isStop.store(true);
											throw std::runtime_error(e.what());
										}

										isStop.store(true);
								    });

	// parse
	while (walker_->GetVisitedLength() || !isStop.load()) {
		auto visitedFiles = walker_->GetVisited();
		if (visitedFiles.empty()) {
			std::this_thread::
				sleep_for(std::chrono::milliseconds(20));
			continue;
		}

		for (const auto& visitedFile : visitedFiles) {
			ParseFile(visitedFile);
		}
	}

	// Wait and check validity of future
	walkingFuture.wait();
	walkingFuture.get();
}

} // galaxycmt

