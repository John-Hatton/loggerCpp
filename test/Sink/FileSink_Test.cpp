//
// Created by John on 10/12/2024.
//
#include <gtest/gtest.h>
#include "Sink/FileSink.hpp"
#include "LogMessage.hpp"
#include <fstream>
#include <cstdio>

class FileSink_Test : public ::testing::Test {
protected:
    FileSink* fileSink;
    std::string testFilename = "test_log.txt";

    void SetUp() override {
        fileSink = new FileSink(testFilename);
    }

    void TearDown() override {
        delete fileSink;
        std::remove(testFilename.c_str()); // Remove the test log file after each test
    }

    std::string readLogFile() {
        std::ifstream file(testFilename);
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
};

// Test FileSink logging output
TEST_F(FileSink_Test, LogOutput) {
    LogMessage logMessage(LogLevel::Info, "Test file log");
    fileSink->log(logMessage);

    std::string output = readLogFile();
    EXPECT_TRUE(output.find("[Info] Test file log") != std::string::npos);
}

// Test empty message handling
TEST_F(FileSink_Test, EmptyMessage) {
    LogMessage logMessage(LogLevel::Warning, "");
    fileSink->log(logMessage);

    std::string output = readLogFile();
    EXPECT_TRUE(output.find("[Warning] ") != std::string::npos);
}

// Test different log levels
TEST_F(FileSink_Test, DifferentLogLevels) {
    LogMessage logMessageDebug(LogLevel::Debug, "Debug message");
    fileSink->log(logMessageDebug);
    std::string output = readLogFile();
    EXPECT_TRUE(output.find("[Debug] Debug message") != std::string::npos);

    LogMessage logMessageError(LogLevel::Error, "Error message");
    fileSink->log(logMessageError);
    output = readLogFile();
    EXPECT_TRUE(output.find("[Error] Error message") != std::string::npos);
}

// Test multiple consecutive log calls
TEST_F(FileSink_Test, MultipleConsecutiveLogs) {
    LogMessage logMessage1(LogLevel::Info, "First log message");
    LogMessage logMessage2(LogLevel::Warning, "Second log message");
    LogMessage logMessage3(LogLevel::Error, "Third log message");

    fileSink->log(logMessage1);
    fileSink->log(logMessage2);
    fileSink->log(logMessage3);

    std::string output = readLogFile();
    EXPECT_TRUE(output.find("[Info] First log message") != std::string::npos);
    EXPECT_TRUE(output.find("[Warning] Second log message") != std::string::npos);
    EXPECT_TRUE(output.find("[Error] Third log message") != std::string::npos);
}

// Test special characters in message
TEST_F(FileSink_Test, SpecialCharactersInMessage) {
    LogMessage logMessage(LogLevel::Info, "Message with special characters: \n \t \" ' !@#$%^&*()");
    fileSink->log(logMessage);

    std::string output = readLogFile();
    EXPECT_TRUE(output.find("Message with special characters: \n \t \" ' !@#$%^&*()") != std::string::npos);
}

// Test very long message
TEST_F(FileSink_Test, VeryLongMessage) {
    std::string longMessage(1000, 'a'); // 1000 'a' characters
    LogMessage logMessage(LogLevel::Info, longMessage);
    fileSink->log(logMessage);

    std::string output = readLogFile();
    EXPECT_TRUE(output.find(longMessage) != std::string::npos);
}
