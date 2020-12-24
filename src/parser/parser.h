#ifndef GALAXYCMT_PARSER_H
#define GALAXYCMT_PARSER_H

#include <string>
#include <memory>

namespace galaxycmt {

class IWalker;

enum class NodeType {
	UNKNOWN   = 0,
	FILE      = 1,
	DIRECTORY = 2
};

struct Node {
	Node(const NodeType& type = NodeType::UNKNOWN,
	     const std::string& path = "")
		: type_(type)
		, path_(path){}
	~Node() = default;

	NodeType type_;
	std::string path_;
};

class IParser {
public:
	IParser() = default;
	~IParser() = default;

	virtual void Parse(const Node& node) = 0;
};

} // galaxycmt

#endif //GALAXYCMT_PARSER_H
