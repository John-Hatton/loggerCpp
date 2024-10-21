//
// Created by John on 10/12/2024.
//

#include "../../include/Sink/ConsoleSink.hpp"

void ConsoleSink::log(const LogMessage &message)
{
            std::cout << message.toString() << std::endl;
}