#include "src/utils/logger/logger.h"

int main(int, char*[])
{
	auto logger = galaxycmt::Logger::GetInstance();
	logger->AddSink(galaxycmt::LoggerSinkType::CONSOLE);
	logger->AddSink(galaxycmt::LoggerSinkType::FILE, "/home/vniksihov/test.log");

	logger->AddMessage("hello world", galaxycmt::SeverityLevel::ERROR);

	return 0;
}

