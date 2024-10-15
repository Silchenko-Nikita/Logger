#pragma once

#include "LogStream.h"

#include <string>
#include <iostream>
#include <mutex>
#include <memory>

class Logger {
public:
    Logger();
    Logger(const std::string& logPrefix);

    Logger(Logger&& other) noexcept;
    Logger& operator=(Logger&& other) noexcept;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    template <typename T>
    LogStream operator<<(const T& message) {
        LogStream logStream(m_loggerImpl, INFO, m_logPrefix);
        logStream << message;
        return logStream;
    }

    LogStream operator()(LogLevel logLevel);

private:
    std::string m_logPrefix{ "" };
    LoggerImpl& m_loggerImpl{ LoggerImpl::getInstance() };
};


Logger getLogger();
Logger getLogger(const std::string& logPrefix);
