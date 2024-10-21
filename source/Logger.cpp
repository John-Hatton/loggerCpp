//
// Created by John on 10/12/2024.
//

#include "Logger.hpp"

std::shared_ptr<Logger> Logger::instance_ = nullptr;

std::shared_ptr<Logger> Logger::instance() {
    static std::once_flag initInstanceFlag;
    std::call_once(initInstanceFlag, []() {
        instance_ = std::shared_ptr<Logger>(new Logger(), [](Logger* logger) {
            // Custom deleter to safely delete the singleton
            delete logger;
        });
    });
    return instance_;
}

Logger::Logger() = default;
Logger::~Logger() = default;

void Logger::Trace(const std::string& message) {
    logMessage(LogLevel::Trace, message);
}

void Logger::Debug(const std::string& message) {
    logMessage(LogLevel::Debug, message);
}

void Logger::Info(const std::string& message) {
    logMessage(LogLevel::Info, message);
}

void Logger::Warning(const std::string& message) {
    logMessage(LogLevel::Warning, message);
}

void Logger::Error(const std::string& message) {
    logMessage(LogLevel::Error, message);
}

void Logger::Critical(const std::string& message) {
    logMessage(LogLevel::Critical, message);
}

void Logger::addSink(std::shared_ptr<Sink> sink) {
    std::lock_guard<std::mutex> lock(mutex_);
    sinks_.push_back(sink);
}

void Logger::setLogLevel(LogLevel level) {
    std::lock_guard<std::mutex> lock(mutex_);
    minLevel_ = level;
}

void Logger::logMessage(LogLevel level, const std::string& message) {
    if (level < minLevel_) return;

    LogMessage logMessage(level, message);

    std::lock_guard<std::mutex> lock(mutex_);
    for (const auto& sink : sinks_) {
        sink->log(logMessage);
    }
}