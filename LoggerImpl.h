#pragma once

#include <string>
#include <iostream>
#include <mutex>

#define ERROR 1
#define WARNING 2
#define DEBUG 3
#define INFO 4

typedef int LogLevel;

class LoggerImpl {
public:
    LoggerImpl(LoggerImpl&& other) noexcept;
    LoggerImpl& operator=(LoggerImpl&& other) noexcept;

    LoggerImpl(const LoggerImpl&) = delete;
    LoggerImpl& operator=(const LoggerImpl&) = delete;

    static LoggerImpl& getInstance();

    void log(LogLevel logLevel, const std::string& logPrefix, const std::string& message);

private:
    LoggerImpl() = default;

    std::string getCurrentDatetimeString();
    std::string getLogLevelString(LogLevel logLevel);

    std::mutex m_logMutex{}; // couldn't find better approach then using mutex 
};
