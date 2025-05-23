//
// Created by John on 10/12/2024.
//

#ifndef LOGGERCPP_LOGFILESINK_HPP
#define LOGGERCPP_LOGFILESINK_HPP

#include "Sink.hpp"
#include "../LogLevel.hpp"
#include <fstream>

class FileSink : public Sink {
public:
    // Declare the explicit constructor
    explicit FileSink(const std::string& filename, LogLevel minLevel = LogLevel::Info);

    // Declare the overridden log method
    void log(const LogMessage& message) override;

private:
    std::ofstream ofs_;  // Member for the file stream
    LogLevel minimumLogLevel;  // Member for the log level
};

#endif //LOGGERCPP_LOGFILESINK_HPP
