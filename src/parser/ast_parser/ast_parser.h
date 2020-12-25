#ifndef GALAXYCMT_AST_PARSER_H
#define GALAXYCMT_AST_PARSER_H

#include <set>
#include <string>

#include "../parser.h"

namespace galaxycmt {

class ASTParser : public IParser {
public:
	explicit ASTParser(const std::shared_ptr<IWalker>& walker = nullptr);
	virtual ~ASTParser() = default;

	void Parse(const Node& node) override;

private:
	void ParseDir(const std::string& pathToDir);
	void ParseFile(const std::string& pathToFile);

	std::shared_ptr<IWalker> walker_;
	std::set<std::string> filesExtensions_;
};

} // galaxycmt

#endif //GALAXYCMT_AST_PARSER_H
