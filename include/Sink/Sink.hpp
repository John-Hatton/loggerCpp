//
// Created by John on 10/12/2024.
//

#ifndef LOGGERCPP_SINK_HPP
#define LOGGERCPP_SINK_HPP

#include "../LogMessage.hpp"

class Sink {
public:
    virtual ~Sink() = default;
    virtual void log(const LogMessage& message) = 0;
};

#endif //LOGGERCPP_SINK_HPP
