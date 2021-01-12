#include <atomic>
#include <future>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "ast_parser.h"
#include "../../walker/walker.h"

namespace galaxycmt {

ASTParser::ASTParser(const std::shared_ptr<IWalker>& walker)
	: walker_(walker) {
	logger_ = Logger::GetInstance();
	keyWords_ = {"ifndef",
	             "define",
	             "include",
	             "namespace",
	             "using",
	             "class",
	             "struct",
	             "public",
	             "protected",
	             "private",
	             "endif"};
	filesExtensions_ = {".h",
					    ".hpp",
					    ".cpp"};
}

void ASTParser::Parse(const Node& node) {
	if (node.type_ == FSNodeType::FILE) {
		ParseFile(node.path_);
		return;
	}

	ParseDir(node.path_);
}

void ASTParser::ParseFile(const std::string& pathToFile) {
	std::string parsedFileExtension = pathToFile.substr(pathToFile.find_last_of('.'));
	if (filesExtensions_.count(parsedFileExtension)) {
		std::fstream parsedFile(pathToFile, std::fstream::in);
		if (!parsedFile.is_open()) {
			logger_->AddMessage("cannot open file: " + pathToFile + "\n");
			return;
		}

		// Parse

	}
}

void ASTParser::ParseDir(const std::string& pathToDir) {
	if (!walker_) {
		return;
	}

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

	while (walker_->GetVisitedLength() || !isStop.load()) {
		auto visitedFiles = walker_->GetVisited();
		if (visitedFiles.empty()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
			continue;
		}

		for (const auto& visitedFile : visitedFiles) {
			ParseFile(visitedFile);
		}
	}

	walkingFuture.wait();
	walkingFuture.get();
}

bool ASTParser::IsVariable(const std::string& textLine) {
	if (textLine.find("/**") != std::string::npos || textLine.find("*/") != std::string::npos) {
		return false;
	}

	std::vector<std::string> splittedTextLine;
	boost::split(splittedTextLine, textLine, boost::is_any_of(" "));

	return std::all_of(splittedTextLine.begin(), splittedTextLine.end(), [&](const std::string& word) -> bool {
		if (keyWords_.count(word)) {
			return false;
		}

		return true;
	});
}

} // galaxycmt

