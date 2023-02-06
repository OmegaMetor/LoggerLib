#pragma once
#include <iostream>
#include <ctime>

class Logger
{
private:
    static Logger *logger;
    Logger(){
    };
    static time_t startTime;

public:
    struct LogOptions{
        int LogLevel = LogLevel::INFO;
        std::string fmt = "[%TH:%TMN:%TS] [%L] at line %LN in [%F]: %M\n";
        std::string LogLevelNames[4] = {
            "DEBUG",
            "INFO",
            "WARNING",
            "ERROR"
        };
    };
    static LogOptions config;
    enum LogLevel
    {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };
    void log(const char *message, int line, const char *file);
    void log(const char *message, LogLevel logLevel, int line, const char *file);
    void log(const char *message);
    void log(const char *message, LogLevel logLevel);
    static Logger &getLogger();
};

#define LOG(message) Logger::getLogger().log(message, Logger::LogLevel::INFO, __LINE__, __FILE__)
#define DEBUG(message) Logger::getLogger().log(message, Logger::LogLevel::DEBUG, __LINE__, __FILE__)
#define WARN(message) Logger::getLogger().log(message, Logger::LogLevel::WARNING, __LINE__, __FILE__)
#define ERROR(message) Logger::getLogger().log(message, Logger::LogLevel::ERROR, __LINE__, __FILE__)
