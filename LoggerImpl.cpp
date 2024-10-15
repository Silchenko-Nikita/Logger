#include "LoggerImpl.h"

#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <utility>

LoggerImpl::LoggerImpl(LoggerImpl&& other) noexcept
    : m_logMutex{} {
}

LoggerImpl& LoggerImpl::operator=(LoggerImpl&& other) noexcept {
    return *this;
}

LoggerImpl& LoggerImpl::getInstance() {
    static LoggerImpl instance;
    return instance;
}

std::string LoggerImpl::getCurrentDatetimeString() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    std::tm local_time;
    localtime_s(&local_time, &now_time);

    std::ostringstream oss;
    oss << std::put_time(&local_time, "%d.%m.%Y %H:%M:%S");

    return oss.str();
}

std::string LoggerImpl::getLogLevelString(LogLevel logLevel) {
    switch (logLevel) {
    case ERROR:
        return "ERROR";
    case WARNING:
        return "WARNING";
    case DEBUG:
        return "DEBUG";
    case INFO:
    default:
        return "INFO";
    }
}

void LoggerImpl::log(LogLevel logLevel, const std::string& logPrefix, const std::string& message) {
    std::lock_guard<std::mutex> guard(m_logMutex);

    std::thread::id threadId = std::this_thread::get_id();
    std::string currentDateTimeStr = getCurrentDatetimeString();
    std::string logLevelStr = getLogLevelString(logLevel);

    std::cout << currentDateTimeStr << "; " << logLevelStr << "; "
              << logPrefix << "(" << threadId << "): "
              << message << std::endl;
}
