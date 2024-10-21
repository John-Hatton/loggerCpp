//
// Created by John on 10/12/2024.
//

#ifndef LOGGERCPP_LOGFILESINK_HPP
#define LOGGERCPP_LOGFILESINK_HPP

#include "Sink.hpp"
#include <fstream>

class FileSink : public Sink {
public:
    explicit FileSink(const std::string& filename)
            : ofs_(filename, std::ios::app) {
        if (!ofs_) {
            throw std::runtime_error("Failed to open log file: " + filename);
        }
    }

    void log(const LogMessage& message) override {
        ofs_ << message.toString() << std::endl;
    }

private:
    std::ofstream ofs_;
};

#endif //LOGGERCPP_LOGFILESINK_HPP
