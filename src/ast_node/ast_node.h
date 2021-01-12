#ifndef GALAXYCMT_AST_NODE_H
#define GALAXYCMT_AST_NODE_H

#include <list>
#include <string>
#include <memory>

namespace galaxycmt {

enum class ASTNodeType {
	UNKNOWN = 0,
	ROOT,
	CLASS,
	STRUCT,
	INCLUDE,
	NAMESPACE,
	USING,
	TYPEDEF,
	INCLUDEGUARD,
	VARIABLE,
	FUNCTION,
	METHOD,
	FIELD,
	ENUM
};

class IASTNode {
public:
	explicit IASTNode(const ASTNodeType& type)
		: type_(type){}
	~IASTNode() = default;

	virtual SetType(const ASTNodeType& type) {
		type_ = type
	}

	virtual ASTNodeType GetType() const {
		return type_;
	}

private:
	ASTNodeType type_;
};

}

#endif //GALAXYCMT_AST_NODE_H
