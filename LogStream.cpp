#include "LogStream.h"

LogStream::LogStream(LoggerImpl& logger, LogLevel logLevel, const std::string& logPrefix)
    : m_logImpl(logger), m_logLevel(logLevel), m_logPrefix(logPrefix) {}

LogStream::~LogStream() {
    flush();
}

LogStream::LogStream(LogStream&& other) noexcept
    : m_logImpl(other.m_logImpl),
    m_logPrefix(other.m_logPrefix),
    m_logLevel(other.m_logLevel),
    m_stream(std::move(other.m_stream)) {

}

LogStream& LogStream::operator=(LogStream&& other) noexcept {
    if (this != &other) {
        m_logImpl = std::move(other.m_logImpl);
        m_logPrefix = std::move(other.m_logPrefix);
        m_logLevel = other.m_logLevel;
        m_stream = std::move(other.m_stream);
    }
    return *this;
}

void LogStream::flush() {
    m_logImpl.log(m_logLevel, m_logPrefix, m_stream.str());
    m_stream.str("");
    m_stream.clear();
}
