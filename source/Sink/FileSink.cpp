//
// Created by John on 10/12/2024.
//

#include "Sink/FileSink.hpp"
#include <stdexcept>     // For std::runtime_error
#include <string>        // For std::string (used in the throw statement, if not already included)

FileSink::FileSink(const std::string& filename, LogLevel minLevel)
    : ofs_(filename, std::ios::app),  // Initialize the file stream in append mode
      minimumLogLevel(minLevel) {     // Initialize the minimum log level
    if (!ofs_) {
        throw std::runtime_error("Failed to open log file: " + filename);
    }
}

// log method implementation with filtering
void FileSink::log(const LogMessage& message) {
    // Check if the message's level is at or above the minimum log level
    if (message.getLevel() >= minimumLogLevel) {
        ofs_ << message.toString() << std::endl;  // Write the message to the file
    }
    // If the message's level is below minimumLogLevel, do nothing
}