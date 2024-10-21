//
// Created by John on 10/12/2024.
//

#include "LogMessage.hpp"
#include <sstream>
#include <iomanip>

LogMessage::LogMessage(LogLevel level, const std::string& message)
        : level_(level), message_(message) {
    timestamp_ = std::chrono::system_clock::now();
}

std::string LogMessage::toString() const {
    std::ostringstream oss;
    oss << "[" << getTimestamp() << "] "
        << "[" << logLevelToString(level_) << "] "
        << message_;
    return oss.str();
}

std::string LogMessage::getTimestamp() const {
    auto in_time_t = std::chrono::system_clock::to_time_t(timestamp_);
    std::ostringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

std::string LogMessage::logLevelToString(LogLevel level) const {
    switch (level) {
        case LogLevel::Trace: return "Trace";
        case LogLevel::Debug: return "Debug";
        case LogLevel::Info: return "Info";
        case LogLevel::Warning: return "Warning";
        case LogLevel::Error: return "Error";
        case LogLevel::Critical: return "Critical";
        default: return "Unknown";
    }
}