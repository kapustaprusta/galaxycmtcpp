#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "logger.h"

namespace galaxycmt {

Logger* Logger::logger_ = 0;
std::mutex Logger::loggerMutex_;
LoggerDestroyer Logger::loggerDestroyer_;

LoggerDestroyer::~LoggerDestroyer() {
	delete logger_;
}

void LoggerDestroyer::Init(Logger* logger) {
	logger_ = logger;
}

Logger* Logger::GetInstance() {
	std::lock_guard lockGuard(loggerMutex_);
	if (!logger_) {
		logger_ = new Logger;
		loggerDestroyer_.Init(logger_);
	}

	return logger_;
}

void Logger::AddSink(const LoggerSinkType& sinkType,
					 const std::string& pathToLogFile) {

}

void Logger::Print(const std::string& message,
                   const SeverityLevel& level)
{
	switch (level)
	{
		case SeverityLevel::TRACE:
			BOOST_LOG_TRIVIAL(trace) << message << "\n";
			break;
		case SeverityLevel::DEBUG:
			BOOST_LOG_TRIVIAL(trace) << message << "\n";
			break;
		case SeverityLevel::INFO:
			BOOST_LOG_TRIVIAL(info) << message << "\n";
			break;
		case SeverityLevel::WARNING:
			BOOST_LOG_TRIVIAL(warning) << message << "\n";
			break;
		case SeverityLevel::ERROR:
			BOOST_LOG_TRIVIAL(error) << message << "\n";
			break;
		case SeverityLevel::FATAL:
			BOOST_LOG_TRIVIAL(fatal) << message << "\n";
			break;
	}
}


} // galaxycmt

