#ifndef GALAXYCMT_AST_PARSER_H
#define GALAXYCMT_AST_PARSER_H

#include <iostream>

#include "../parser.h"

namespace galaxycmt
{

class ASTParser : public IParser
{
public:
	explicit ASTParser(const std::shared_ptr<IWalker>& walker = nullptr)
		: IParser(walker){}
	virtual ~ASTParser() = default;

	bool Parse() override;
	bool Parse(const std::string& pathToFile) override;

private:
};

} // galaxycmt

#endif //GALAXYCMT_AST_PARSER_H
