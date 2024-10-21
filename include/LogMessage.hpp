//
// Created by John on 10/12/2024.
//

#ifndef LOGGERCPP_LOGMESSAGE_HPP
#define LOGGERCPP_LOGMESSAGE_HPP

#include "LogLevel.hpp"
#include <string>
#include <chrono>

class LogMessage {
public:
    LogMessage(LogLevel level, const std::string& message);
    std::string toString() const;

private:
    LogLevel level_;
    std::string message_;
    std::chrono::system_clock::time_point timestamp_;

    std::string getTimestamp() const;
    std::string logLevelToString(LogLevel level) const;
};


#endif //LOGGERCPP_LOGMESSAGE_HPP
