#include "LoggerLib.h"
#include <iostream>

Logger *Logger::logger = nullptr;
Logger::LogOptions Logger::config;
void Logger::log(const char *message, LogLevel logLevel, int line, const char *file)
{

    if(!(logLevel >= Logger::config.LogLevel)){
        return;
    }

    std::string output = Logger::config.fmt;
    size_t pos;
    pos = output.find("%M");
    if (pos != std::string::npos) {
      output.replace(pos, 2, message);
    }
    pos = output.find("%LN");
    if (pos != std::string::npos) {
      output.replace(pos, 3, std::to_string(line));
    }
    pos = output.find("%F");
    if (pos != std::string::npos) {
      output.replace(pos, 2, file);
    }
    pos = output.find("%L");
    if (pos != std::string::npos) {
      output.replace(pos, 2, Logger::config.LogLevelNames[logLevel]);
    }

    std::cout << output << std::endl;   
};

void Logger::log(const char *message, int line, const char *file)
{
    Logger::log(message, Logger::LogLevel::INFO, line, file);
};

void Logger::log(const char *message, LogLevel logLevel)
{
    Logger::log(message, logLevel, -1, "Unknown");
};

void Logger::log(const char *message)
{
    Logger::log(message, Logger::LogLevel::INFO, -1, "Unknown");
};

Logger &Logger::getLogger()
{
    if (!Logger::logger)
        Logger::logger = new Logger();
    return *Logger::logger;
}
