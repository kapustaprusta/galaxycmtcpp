#include <fstream>
#include <iostream>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>

#include "logger.h"

namespace galaxycmt {

namespace logging = boost::log;
namespace sinks   = boost::log::sinks;

typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;

std::mutex Logger::loggerMutex_;
Logger* Logger::logger_ = nullptr;
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

void Logger::AddSink(const LoggerSinkType& sinkType, const std::string& pathToFile) {
	switch (sinkType) {
		case LoggerSinkType::FILE:
			AddFileSink(pathToFile);
			break;
		case LoggerSinkType::CONSOLE:
			AddConsoleSink();
			break;
		default:
			break;
	}
}

void Logger::AddMessage(const std::string& message, const SeverityLevel& level)
{
	switch (level)
	{
		case SeverityLevel::TRACE:
			BOOST_LOG(coreLogger_) << message << "\n";
			break;
		case SeverityLevel::DEBUG:
			BOOST_LOG(coreLogger_) << message << "\n";
			break;
		case SeverityLevel::INFO:
			BOOST_LOG(coreLogger_) << message << "\n";
			break;
		case SeverityLevel::WARNING:
			BOOST_LOG(coreLogger_) << message << "\n";
			break;
		case SeverityLevel::ERROR:
			BOOST_LOG(coreLogger_) << message << "\n";
			break;
		case SeverityLevel::FATAL:
			BOOST_LOG(coreLogger_) << message << "\n";
			break;
	}
}

void Logger::AddFileSink(const std::string& pathToFile) {
	auto logStream = boost::make_shared<std::ofstream>(pathToFile);
	auto logSink = boost::make_shared<text_sink>();
	logSink->locked_backend()->add_stream(logStream);
	logging::core::get()->add_sink(logSink);
}

void Logger::AddConsoleSink() {
	auto logStream = boost::shared_ptr<std::ostream>(&std::clog, boost::null_deleter());
	auto logSink = boost::make_shared<text_sink>();
	logSink->locked_backend()->add_stream(logStream);
	logging::core::get()->add_sink(logSink);
}

} // galaxycmt

