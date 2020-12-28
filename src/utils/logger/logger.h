#ifndef GALAXYCMT_LOGGER_H
#define GALAXYCMT_LOGGER_H

#include <list>
#include <mutex>
#include <memory>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace galaxycmt {

class Logger;

namespace src = boost::log::sources;

enum class SeverityLevel {
	TRACE   = 0,
	DEBUG   = 1,
	INFO    = 2,
	WARNING = 3,
	ERROR   = 4,
	FATAL   = 5
};

enum class LoggerSinkType {
	FILE    = 0,
	CONSOLE = 1
};

class LoggerDestroyer {
public:
	LoggerDestroyer() = default;
	~LoggerDestroyer();

	void Init(Logger* logger);

private:
	Logger* logger_;
};

class Logger {
public:
	Logger(Logger& logger) = delete;
	void operator=(const Logger& logger) = delete;

	static Logger* GetInstance();

	void AddSink(const LoggerSinkType& sinkType,
			     const std::string& pathToFile = "");

	void AddMessage(const std::string& message,
	                const SeverityLevel& level = SeverityLevel::INFO);

private:
	friend LoggerDestroyer;

	Logger() = default;
	~Logger() = default;

	void AddConsoleSink();
	void AddFileSink(const std::string& pathToFile);

	src::logger coreLogger_;

	static Logger* logger_;
	static std::mutex loggerMutex_;
	static LoggerDestroyer loggerDestroyer_;
};

} // galaxycmt

#endif //GALAXYCMT_LOGGER_H
