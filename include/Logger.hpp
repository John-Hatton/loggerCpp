//
// Created by John on 10/12/2024.
//

#ifndef LOGGERCPP_LOGGER_HPP
#define LOGGERCPP_LOGGER_HPP


#include "Sink/Sink.hpp"
#include "LogLevel.hpp"
#include "LogMessage.hpp"
#include <vector>
#include <memory>
#include <mutex>
#include <string>

class Logger {
public:
    static std::shared_ptr<Logger> instance();

    // Delete copy constructor and assignment operator to prevent copies
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    // Methods for different log levels
    void Trace(const std::string& message);
    void Debug(const std::string& message);
    void Info(const std::string& message);
    void Warning(const std::string& message);
    void Error(const std::string& message);
    void Critical(const std::string& message);

    // Configuration methods
    void addSink(std::shared_ptr<Sink> sink);
    void setLogLevel(LogLevel level);

private:
    Logger();
    ~Logger();

    static std::shared_ptr<Logger> instance_;

    void logMessage(LogLevel level, const std::string& message);

    LogLevel minLevel_ = LogLevel::Info;
    std::vector<std::shared_ptr<Sink>> sinks_;
    std::mutex mutex_;
};


#endif //LOGGERCPP_LOGGER_HPP
