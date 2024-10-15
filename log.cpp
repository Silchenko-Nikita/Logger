#include "log.h"

#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <utility>

Logger::Logger() {
}

Logger::Logger(const std::string& logPrefix) : m_logPrefix{logPrefix} {
}

Logger::Logger(Logger&& other) noexcept {
    m_loggerImpl = std::move(other.m_loggerImpl);
    m_logPrefix = std::move(other.m_logPrefix);
}

Logger& Logger::operator=(Logger&& other) noexcept {
    if (this != &other) {
        m_loggerImpl = std::move(other.m_loggerImpl);
        m_logPrefix = std::move(other.m_logPrefix);
    }
    return *this;
}

LogStream Logger::operator()(LogLevel logLevel) {
    return LogStream(m_loggerImpl, logLevel, m_logPrefix);
}

Logger getLogger() {
    return std::move(Logger());
}

Logger getLogger(const std::string& logPrefix) {
    return std::move(Logger(logPrefix));
}
