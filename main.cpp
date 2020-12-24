#include <memory>
#include <iostream>

#include "src/walker/dir_walker/dir_walker.h"
#include "src/parser/ast_parser/ast_parser.h"

int main()
{
	galaxycmt::WalkerConfig config = {true};
	std::shared_ptr<galaxycmt::IWalker> walker = std::make_shared<galaxycmt::DirWalker>(config);
	std::unique_ptr<galaxycmt::IParser> parser = std::make_unique<galaxycmt::ASTParser>(walker);

	galaxycmt::Node node = {galaxycmt::NodeType::DIRECTORY,
						    "/home/vniksihov/src/cpp/galaxycmt/src"};

	try {
		parser->Parse(node);
	}
	catch (std::exception& e) {
		std::cout << e.what() << "\n";
	}


	return 0;
}
