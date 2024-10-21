//
// Created by John on 10/12/2024.
//
#include <gtest/gtest.h>
#include "Logger.hpp"
#include "Sink/ConsoleSink.hpp"
#include "Sink/FileSink.hpp"
#include <sstream>
#include <fstream>
#include <cstdio>
#include <thread>
#include <chrono>

class Logger_Test : public ::testing::Test {
protected:
    std::shared_ptr<Logger> logger = Logger::instance();
    std::streambuf* originalCoutBuffer;
    std::ostringstream testOutput;
    std::string testFilename = "test_logger_log.txt";
    std::shared_ptr<ConsoleSink> consoleSink;
    std::shared_ptr<FileSink> fileSink;

    void SetUp() override {
        originalCoutBuffer = std::cout.rdbuf(); // Save the original buffer
        std::cout.rdbuf(testOutput.rdbuf());    // Redirect cout to our ostringstream

        consoleSink = std::make_shared<ConsoleSink>();
        fileSink = std::make_shared<FileSink>(testFilename);

        logger->addSink(consoleSink);
        logger->addSink(fileSink);
    }

    void TearDown() override {
        std::cout.rdbuf(originalCoutBuffer); // Restore the original buffer
        std::remove(testFilename.c_str()); // Remove the test log file after each test
    }

    std::string readLogFile() {
        std::ifstream file(testFilename);
        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
    }
};

// Test logging at different levels
TEST_F(Logger_Test, LogAtDifferentLevels) {
    logger->setLogLevel(LogLevel::Trace); // Ensure all levels are logged
    logger->Info("Test Info log");
    logger->Debug("Test Debug log");
    logger->Error("Test Error log");

    // Allow some time for the logs to be written
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::string consoleOutput = testOutput.str();
    EXPECT_TRUE(consoleOutput.find("[Info] Test Info log") != std::string::npos);
    EXPECT_TRUE(consoleOutput.find("[Debug] Test Debug log") != std::string::npos);
    EXPECT_TRUE(consoleOutput.find("[Error] Test Error log") != std::string::npos);

    std::string fileOutput = readLogFile();
    EXPECT_TRUE(fileOutput.find("[Info] Test Info log") != std::string::npos);
    EXPECT_TRUE(fileOutput.find("[Debug] Test Debug log") != std::string::npos);
    EXPECT_TRUE(fileOutput.find("[Error] Test Error log") != std::string::npos);
}

// Test setting log level
TEST_F(Logger_Test, SetLogLevel) {
    logger->setLogLevel(LogLevel::Warning);
    logger->Debug("This should not be logged");
    logger->Warning("This should be logged");

    // Allow some time for the logs to be written
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::string consoleOutput = testOutput.str();
    EXPECT_TRUE(consoleOutput.find("This should not be logged") == std::string::npos);
    EXPECT_TRUE(consoleOutput.find("[Warning] This should be logged") != std::string::npos);

    std::string fileOutput = readLogFile();
    EXPECT_TRUE(fileOutput.find("This should not be logged") == std::string::npos);
    EXPECT_TRUE(fileOutput.find("[Warning] This should be logged") != std::string::npos);
}

// Test multiple sinks
TEST_F(Logger_Test, MultipleSinks) {
    logger->Info("Logging to multiple sinks");

    // Allow some time for the logs to be written
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::string consoleOutput = testOutput.str();
    EXPECT_TRUE(consoleOutput.find("[Info] Logging to multiple sinks") != std::string::npos);

    std::string fileOutput = readLogFile();
    EXPECT_TRUE(fileOutput.find("[Info] Logging to multiple sinks") != std::string::npos);
}

// Test thread safety of logger
TEST_F(Logger_Test, ThreadSafety) {
    auto logTask = [&]() {
        for (int i = 0; i < 100; ++i) {
            logger->Info("Thread logging test " + std::to_string(i));
        }
    };

    std::thread t1(logTask);
    std::thread t2(logTask);
    t1.join();
    t2.join();

    // Allow some time for the logs to be written
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    std::string fileOutput = readLogFile();
    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(fileOutput.find("Thread logging test " + std::to_string(i)) != std::string::npos);
    }
}