//
// Created by John on 10/12/2024.
//
#include <gtest/gtest.h>
#include "Sink/ConsoleSink.hpp"
#include "LogMessage.hpp"
#include <sstream>
#include <iostream>

class ConsoleSink_Test : public ::testing::Test {
protected:
    ConsoleSink* consoleSink;
    std::streambuf* originalCoutBuffer;
    std::ostringstream testOutput;

    void SetUp() override {
        consoleSink = new ConsoleSink();
        originalCoutBuffer = std::cout.rdbuf(); // Save the original buffer
        std::cout.rdbuf(testOutput.rdbuf());    // Redirect cout to our ostringstream
    }

    void TearDown() override {
        delete consoleSink;
        std::cout.rdbuf(originalCoutBuffer); // Restore the original buffer
    }
};

// Test ConsoleSink logging output
TEST_F(ConsoleSink_Test, LogOutput) {
    LogMessage logMessage(LogLevel::Info, "Test console log");
    consoleSink->log(logMessage);

    std::string output = testOutput.str();
    EXPECT_TRUE(output.find("[Info] Test console log") != std::string::npos);
}

// Test empty message handling
TEST_F(ConsoleSink_Test, EmptyMessage) {
    LogMessage logMessage(LogLevel::Warning, "");
    consoleSink->log(logMessage);

    std::string output = testOutput.str();
    EXPECT_TRUE(output.find("[Warning] ") != std::string::npos);
}

// Test different log levels
TEST_F(ConsoleSink_Test, DifferentLogLevels) {
    LogMessage logMessageDebug(LogLevel::Debug, "Debug message");
    consoleSink->log(logMessageDebug);
    EXPECT_TRUE(testOutput.str().find("[Debug] Debug message") != std::string::npos);

    LogMessage logMessageError(LogLevel::Error, "Error message");
    consoleSink->log(logMessageError);
    EXPECT_TRUE(testOutput.str().find("[Error] Error message") != std::string::npos);
}


// Test multiple consecutive log calls
TEST_F(ConsoleSink_Test, MultipleConsecutiveLogs) {
    LogMessage logMessage1(LogLevel::Info, "First log message");
    LogMessage logMessage2(LogLevel::Warning, "Second log message");
    LogMessage logMessage3(LogLevel::Error, "Third log message");

    consoleSink->log(logMessage1);
    consoleSink->log(logMessage2);
    consoleSink->log(logMessage3);

    std::string output = testOutput.str();
    EXPECT_TRUE(output.find("[Info] First log message") != std::string::npos);
    EXPECT_TRUE(output.find("[Warning] Second log message") != std::string::npos);
    EXPECT_TRUE(output.find("[Error] Third log message") != std::string::npos);
}

// Test special characters in message
TEST_F(ConsoleSink_Test, SpecialCharactersInMessage) {
    LogMessage logMessage(LogLevel::Info, "Message with special characters: \n \t \" ' !@#$%^&*()");
    consoleSink->log(logMessage);

    std::string output = testOutput.str();
    EXPECT_TRUE(output.find("Message with special characters: \n \t \" ' !@#$%^&*()") != std::string::npos);
}

// Test very long message
TEST_F(ConsoleSink_Test, VeryLongMessage) {
    std::string longMessage(1000, 'a'); // 1000 'a' characters
    LogMessage logMessage(LogLevel::Info, longMessage);
    consoleSink->log(logMessage);

    std::string output = testOutput.str();
    EXPECT_TRUE(output.find(longMessage) != std::string::npos);
}
