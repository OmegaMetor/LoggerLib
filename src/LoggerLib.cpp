#include "LoggerLib.h"
#include <iostream>
#include <ctime>

time_t Logger::startTime = time(nullptr);
Logger *Logger::logger = nullptr;
Logger::LogOptions Logger::config;
void Logger::log(const char *message, LogLevel logLevel, int line, const char *file)
{
  if (!(logLevel >= Logger::config.LogLevel))
    return;

  std::time_t epochTime = (time(nullptr) - Logger::startTime);
  tm *epoch = localtime(&epochTime);
  int epochHours = epoch->tm_hour + (epoch->tm_yday * 24);
  int epochMinutes = epoch->tm_min;
  int epochSeconds = epoch->tm_sec;
  tm *time = localtime(&Logger::startTime);

  std::string output = Logger::config.fmt;
  size_t pos;
  pos = output.find("%TY");
  if (pos != std::string::npos)
  {
    output.replace(pos, 3, std::string(std::to_string(time->tm_year).length() > 1 ? 0 : 2 - std::to_string(time->tm_year).length(), '0').append(std::to_string(time->tm_year)));
  }
  pos = output.find("%TD");
  if (pos != std::string::npos)
  {
    output.replace(pos, 3, std::string(std::to_string(time->tm_mday).length() > 1 ? 0 : 2 - std::to_string(time->tm_mday).length(), '0').append(std::to_string(time->tm_mday)));
  }
  pos = output.find("%TH");
  if (pos != std::string::npos)
  {
    output.replace(pos, 3, std::string(std::to_string(time->tm_hour).length() > 1 ? 0 : 2 - std::to_string(time->tm_hour).length(), '0').append(std::to_string(time->tm_hour)));
  }
  pos = output.find("%TMN");
  if (pos != std::string::npos)
  {
    output.replace(pos, 4, std::string(std::to_string(time->tm_min).length() > 1 ? 0 : 2 - std::to_string(time->tm_min).length(), '0').append(std::to_string(time->tm_min)));
  }
  pos = output.find("%TM");
  if (pos != std::string::npos)
  {
    output.replace(pos, 3, std::string(std::to_string(time->tm_mon).length() > 1 ? 0 : 2 - std::to_string(time->tm_mon).length(), '0').append(std::to_string(time->tm_mon)));
  }
  pos = output.find("%TS");
  if (pos != std::string::npos)
  {
    output.replace(pos, 3, std::string(std::to_string(time->tm_sec).length() > 1 ? 0 : 2 - std::to_string(time->tm_sec).length(), '0').append(std::to_string(time->tm_sec)));
  }

  pos = output.find("%EH");
  if (pos != std::string::npos)
  {
    output.replace(pos, 3, std::string(std::to_string(epochHours).length() > 1 ? 0 : 2 - std::to_string(epochHours).length(), '0').append(std::to_string(epochHours)));
  }
  pos = output.find("%EMN");
  if (pos != std::string::npos)
  {
    output.replace(pos, 4, std::string(std::to_string(epochMinutes).length() > 1 ? 0 : 2 - std::to_string(epochMinutes).length(), '0').append(std::to_string(epochMinutes)));
  }
  pos = output.find("%ES");
  if (pos != std::string::npos)
  {
    output.replace(pos, 3, std::string(std::to_string(epochSeconds).length() > 1 ? 0 : 2 - std::to_string(epochSeconds).length(), '0').append(std::to_string(epochSeconds)));
  }

  pos = output.find("%M");
  if (pos != std::string::npos)
  {
    output.replace(pos, 2, message);
  }
  pos = output.find("%LN");
  if (pos != std::string::npos)
  {
    output.replace(pos, 3, std::to_string(line));
  }
  pos = output.find("%F");
  if (pos != std::string::npos)
  {
    output.replace(pos, 2, file);
  }
  pos = output.find("%L");
  if (pos != std::string::npos)
  {
    output.replace(pos, 2, Logger::config.LogLevelNames[logLevel]);
  }

  std::cout << output;
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
