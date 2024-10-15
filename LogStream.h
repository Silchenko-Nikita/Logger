#pragma once

#include "LoggerImpl.h"

#include <sstream>
#include <string>

class LogStream {
public:
    LogStream(LoggerImpl& logger, LogLevel logLevel, const std::string& logPrefix);
    ~LogStream();

    LogStream(LogStream&& other) noexcept;
    LogStream& operator=(LogStream&& other) noexcept;

    LogStream(const LogStream&) = delete;
    LogStream& operator=(const LogStream&) = delete;

    template <typename T>
    LogStream& operator<<(const T& message) {
        m_stream << message;
        return *this;
    }

private:
    void flush();

    LoggerImpl& m_logImpl;
    std::string m_logPrefix{ "" };
    LogLevel m_logLevel{ INFO };
    std::ostringstream m_stream{};
};
