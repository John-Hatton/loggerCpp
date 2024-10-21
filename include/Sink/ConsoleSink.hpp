//
// Created by John on 10/12/2024.
//

#ifndef LOGGERCPP_CONSOLESINK_HPP
#define LOGGERCPP_CONSOLESINK_HPP

#include "Sink.hpp"
#include <iostream>

class ConsoleSink : public Sink {
public:
    void log(const LogMessage& message) override;
};

#endif //LOGGERCPP_CONSOLESINK_HPP
