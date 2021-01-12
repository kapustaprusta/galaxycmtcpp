#include <memory>

#include "src/utils/logger/logger.h"
#include "src/parser/ast_parser/ast_parser.h"

int main(int, char*[])
{
	auto logger = galaxycmt::Logger::GetInstance();
	logger->AddSink(galaxycmt::LoggerSinkType::CONSOLE);

	auto parser = std::make_shared<galaxycmt::ASTParser>();
	parser->Parse(galaxycmt::FSNode{galaxycmt::FSNodeType::FILE, "/home/vniksihov/CCLK.h"});

	return 0;
}

