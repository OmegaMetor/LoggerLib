#include "LoggerLib.h"

int main()
{
    Logger::LogOptions config = Logger::LogOptions();
    config.fmt = "[%L] at line %LN in [%F]: %M";
    config.LogLevel = Logger::LogLevel::INFO;
    Logger::getLogger().config = config;
    DEBUG("Debug here!");
    LOG("Log here!");
    WARN("Warning here!");
    ERROR("Error here!");
    return 0;
}