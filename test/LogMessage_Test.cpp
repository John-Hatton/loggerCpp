//
// Created by John on 10/12/2024.
//
#include <gtest/gtest.h>
#include "LogMessage.hpp"


class LogMessage_Test : public ::testing::Test {
protected:

    LogMessage* logMessage;

    void SetUp() override {
        logMessage = nullptr;
    }

    void TearDown() override {
        delete logMessage;
    }
};

// Test LogMessage constructor and toString output
TEST_F(LogMessage_Test, ConstructorAndToString) {
    logMessage = new LogMessage(LogLevel::Info, "Test message");
    std::string expectedOutput = "[";
    expectedOutput += logMessage->toString().substr(1, 19); // To include timestamp
    expectedOutput += "] [Info] Test message";
    EXPECT_TRUE(logMessage->toString().find(expectedOutput) != std::string::npos);
}

// Test log level to string conversion
TEST_F(LogMessage_Test, LogLevelToStringConversion) {
    logMessage = new LogMessage(LogLevel::Debug, "Debug level message");
    EXPECT_TRUE(logMessage->toString().find("[Debug]") != std::string::npos);
}

// Test timestamp inclusion
TEST_F(LogMessage_Test, TimestampIncluded) {
    logMessage = new LogMessage(LogLevel::Warning, "Check timestamp");
    EXPECT_FALSE(logMessage->toString().empty());
    EXPECT_TRUE(logMessage->toString().find("[") != std::string::npos);
}

// Test empty message handling
TEST_F(LogMessage_Test, EmptyMessage) {
    logMessage = new LogMessage(LogLevel::Info, "");
    EXPECT_TRUE(logMessage->toString().find("[Info] ") != std::string::npos);
}

// Test different log levels
TEST_F(LogMessage_Test, DifferentLogLevels) {
    logMessage = new LogMessage(LogLevel::Error, "Error message");
    EXPECT_TRUE(logMessage->toString().find("[Error]") != std::string::npos);

    delete logMessage;
    logMessage = new LogMessage(LogLevel::Critical, "Critical message");
    EXPECT_TRUE(logMessage->toString().find("[Critical]") != std::string::npos);

    delete logMessage;
    logMessage = new LogMessage(LogLevel::Trace, "Trace message");
    EXPECT_TRUE(logMessage->toString().find("[Trace]") != std::string::npos);
}

// Test timestamp formatting
TEST_F(LogMessage_Test, TimestampFormatting) {
    logMessage = new LogMessage(LogLevel::Info, "Test timestamp format");
    std::string timestamp = logMessage->toString().substr(1, 19);
    EXPECT_EQ(timestamp.length(), 19);
    EXPECT_TRUE(timestamp[4] == '-' && timestamp[7] == '-' && timestamp[10] == ' ' && timestamp[13] == ':' && timestamp[16] == ':');
}

// Test message content
TEST_F(LogMessage_Test, MessageContent) {
    logMessage = new LogMessage(LogLevel::Warning, "This is a test warning message");
    EXPECT_TRUE(logMessage->toString().find("This is a test warning message") != std::string::npos);
}