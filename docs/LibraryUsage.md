# LibraryUsage.md

## Introduction

This guide will help you integrate and use the LoggerCpp library in your project. LoggerCpp is a lightweight, easy-to-use C++ logging library that provides different log levels and supports multiple sinks (e.g., Console, File). By following this document, you will learn how to set up the library using CMake and start logging quickly in your project.

## Setting Up LoggerCpp with CMake

### Step 1: Adding `FindLoggerCpp.cmake`

LoggerCpp provides a `FindLoggerCpp.cmake` file to make the integration process seamless. To begin:

1. **Add `FindLoggerCpp.cmake` to Your Project**:
    - Place the `FindLoggerCpp.cmake` script in a `cmake` directory at the root of your project.

   Your project structure should look like this:

   ```
   MyProject/
   ├── cmake/
   │   └── FindLoggerCpp.cmake
   ├── src/
   │   └── main.cpp
   └── CMakeLists.txt
   ```

### Step 2: Set Environment Variables

LoggerCpp requires two environment variables to be set in order to find the include and library directories:

- **Linux/macOS**:
  ```sh
  export LOGGERCPP_INCLUDE_DIR=/path/to/loggerCpp/include
  export LOGGERCPP_LIB_DIR=/path/to/loggerCpp/build
  ```

- **Windows (Command Prompt)**:
  ```cmd
  set LOGGERCPP_INCLUDE_DIR=C:\path\to\loggerCpp\include
  set LOGGERCPP_LIB_DIR=C:\path\to\loggerCpp\build
  ```

These variables should point to the correct locations for the `loggerCpp` include directory and the library directory.

### Step 3: Modify `CMakeLists.txt`

- **Root `CMakeLists.txt`**:
  Add the following lines to your root `CMakeLists.txt` to find the logger library.

  ```cmake
  # Add cmake directory to module path
  set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

  # Find loggerCpp library
  find_package(loggerCpp REQUIRED)
  ```

- **Source Directory `CMakeLists.txt`** (e.g., `src/CMakeLists.txt`):
  Link the loggerCpp library and include its headers.

  ```cmake
  # Link necessary libraries
  target_link_libraries(${PROJECT_NAME} PRIVATE loggerCpp::loggerCpp)

  # Include the loggerCpp headers
  target_include_directories(${PROJECT_NAME} PRIVATE ${LOGGERCPP_INCLUDE_DIRS})
  ```

After adding these changes, you're ready to build your project and start using LoggerCpp.

## Using LoggerCpp

### Initializing the Logger

The first step in using LoggerCpp is to initialize the logger in a central place, such as in the `main()` function or in a setup function within a test case. Here's an example of how to initialize the logger:

```cpp
#include "Logger.hpp"
#include "Sink/ConsoleSink.hpp"

int main() {
    auto log = Logger::instance();
    log->addSink(std::make_shared<ConsoleSink>());
    log->setLogLevel(LogLevel::Trace);

    log->Debug("LoggerCpp Initialized Successfully...");

    // Your application code here
    return 0;
}
```

### Logging in Project Files

In other parts of your project, you may want to use the logger within classes. Here is an example of how to use the logger in class members:

1. **Declare a Logger in the Class**:

   ```cpp
   #include "Logger.hpp"
   
   class ConfigurationManager {
   public:
       ConfigurationManager() : log(Logger::instance()) {}

       void installDependency(const std::string& dependencyName) {
           log->Debug("Installing Dependency " + dependencyName + "...");
       }

   private:
       std::shared_ptr<Logger> log;
   };
   ```

2. **Using the Logger**:
    - **Constructor Initialization**: Initialize the `log` member in the constructor initializer list using `Logger::instance()`, which returns a `std::shared_ptr<Logger>`.
    - **Logging Example**: Use `log->Debug(...)` to log messages from the instance.

### Example Usage

```cpp
#include "Logger.hpp"
#include "Sink/ConsoleSink.hpp"
#include "Sink/FileSink.hpp"

int main() {
    // Initialize logger with console and file sinks
    auto log = Logger::instance();
    log->addSink(std::make_shared<ConsoleSink>());
    log->addSink(std::make_shared<FileSink>("app.log"));
    log->setLogLevel(LogLevel::Info);

    // Log messages at different levels
    log->Info("Application started.");
    log->Warning("This is a warning.");
    log->Error("An error occurred.");

    return 0;
}
```

In the above example, we initialize the logger and add two sinks—console and file. This allows the logger to output messages both to the console and to a file named `app.log`.

## Best Practices

- **Centralized Initialization**: Initialize the logger once in a central location (e.g., in `main()`). This ensures consistency throughout the application.
- **Use Appropriate Log Levels**: Use different log levels (`Trace`, `Debug`, `Info`, `Warning`, `Error`, `Critical`) to categorize your log messages effectively. This helps with filtering and understanding logs during debugging and production.
- **Pass Logger by Reference**: When using the logger within classes, pass a `std::shared_ptr<Logger>` by reference or store it as a member to avoid redundant initializations.

## Conclusion

Integrating LoggerCpp into your project is straightforward with the provided `FindLoggerCpp.cmake` script. By following the steps outlined above, you can quickly set up logging and add valuable debug and information logs to your application. This will significantly help in monitoring, debugging, and maintaining your software effectively.

