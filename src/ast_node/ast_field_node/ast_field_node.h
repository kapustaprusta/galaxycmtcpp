#ifndef GALAXYCMT_AST_FIELD_NODE_H
#define GALAXYCMT_AST_FIELD_NODE_H

#include <list>
#include <string>

#include "../ast_node.h"

namespace galaxycmt {

class ASTFieldNode : public IASTNode {
public:
	ASTFieldNode()
		: IASTNode(ASTNodeType::FIELD){}
	virtual ~ASTFieldNode() = default;

private:
	std::string comment_;
	std::string fieldType_;
	std::string default_val_;
	std::string access_modifier_;
	std::list<std::string> modifiers_;
};

}

#endif //GALAXYCMT_AST_FIELD_NODE_H
