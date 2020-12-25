#ifndef GALAXYCMT_LOGGER_H
#define GALAXYCMT_LOGGER_H

#include <list>
#include <mutex>
#include <memory>

namespace galaxycmt {

class Logger;

typedef boost::log::sinks::sink sink;

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
			     const std::string& pathToLogFile = "");

	void Print(const std::string& message,
			   const SeverityLevel& level);

private:
	friend LoggerDestroyer;

	Logger() = default;
	~Logger() = default;

	static Logger* logger_;
	static std::mutex loggerMutex_;
	static LoggerDestroyer loggerDestroyer_;
};

} // galaxycmt

#endif //GALAXYCMT_LOGGER_H
