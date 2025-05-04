# LoggerCpp

LoggerCpp is a lightweight and easy-to-use C++ logging library inspired by Serilog. It provides different logging levels and supports multiple sinks (e.g., Console, File). This README will guide you on how to install, use, and integrate LoggerCpp into your projects.

## Features

- **Multiple Log Levels**: Trace, Debug, Info, Warning, Error, Critical.
- **Multiple Sinks**: Output logs to the console, files, or both.
- **Thread-Safe Singleton Logger**: Safe for use in multi-threaded environments.
- **Simple Integration**: Easy to integrate into any C++ project using CMake.

## Installation

### Using `FindLoggerCpp.cmake`

LoggerCpp comes with a `FindLoggerCpp.cmake` script to make integration seamless. Follow these steps to install and use the logger in your project:

1. **Clone the Repository**:

   ```sh
   git clone https://github.com/yourusername/loggerCpp.git
   ```

2. **Build the Library**:

   Navigate to the `loggerCpp` directory and create a build directory:

   ```sh
   cd loggerCpp
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```

   This will generate the `libLoggerCpp.a` (Linux/macOS) or `LoggerCpp.lib` (Windows) file in the `build` directory.

   NOTE: If in Linux, you will need to change the file in the `cmake` directory from `FindLoggerCpp.cmake` to `FindloggerCpp.cmake`

4. **Set Environment Variables**:

   Set the environment variables to provide hints to the `FindLoggerCpp.cmake` script:

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

5. **Integrate LoggerCpp in Your Project**:

    - Add the path to `FindLoggerCpp.cmake` in your project's CMake configuration.
    - Use `find_package(loggerCpp REQUIRED)` to locate the library.
    - Link the library to your executable.

   Example `CMakeLists.txt` for your project:

   ```cmake
   cmake_minimum_required(VERSION 3.10)
   project(HelloWorld)

   # Add the path to FindLoggerCpp.cmake
   list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

   # Find the loggerCpp package
   find_package(loggerCpp REQUIRED)

   # Add the executable
   add_executable(HelloWorld src/main.cpp)

   # Link with the loggerCpp library
   target_link_libraries(HelloWorld PRIVATE loggerCpp::loggerCpp)

   # Include the loggerCpp headers
   target_include_directories(HelloWorld PRIVATE ${LOGGERCPP_INCLUDE_DIRS})
   ```

## Usage

### Basic Logging Example

1. **Include the Logger Header**:

   ```cpp
   #include "Logger.hpp"
   ```

2. **Use the Logger**:

   ```cpp
   int main() {
       auto& logger = Logger::instance();
       logger.Info("Hello, World! This is a log message.");
       logger.Debug("This is a debug message.");
       logger.Error("An error occurred.");
       return 0;
   }
   ```

### Setting Up Sinks

By default, LoggerCpp supports multiple sinks. You can log to the console, files, or both.

- **Console Sink**:

  ```cpp
  #include "Sink/ConsoleSink.hpp"
  logger.addSink(std::make_shared<ConsoleSink>());
  ```

- **File Sink**:

  ```cpp
  #include "Sink/FileSink.hpp"
  logger.addSink(std::make_shared<FileSink>("app.log"));
  ```

### Log Levels

LoggerCpp provides the following log levels:
- `Trace` – Verbose information for diagnosing issues.
- `Debug` – Debugging information.
- `Info` – General information about application flow.
- `Warning` – Indications of potential issues.
- `Error` – Errors that prevent parts of the program from functioning.
- `Critical` – Severe errors that require immediate attention.

### Example Usage with Different Log Levels

```cpp
logger.Trace("Trace level message");
logger.Debug("Debug level message");
logger.Info("Info level message");
logger.Warning("Warning level message");
logger.Error("Error level message");
logger.Critical("Critical level message");
```

## Thread Safety

LoggerCpp uses a thread-safe singleton pattern and mutexes to ensure that logs are properly synchronized across multiple threads. Here’s an example of using LoggerCpp in a multi-threaded environment:

```cpp
#include <thread>

void logTask(int id) {
    auto& logger = Logger::instance();
    logger.Info("Logging from thread " + std::to_string(id));
}

int main() {
    std::thread t1(logTask, 1);
    std::thread t2(logTask, 2);
    t1.join();
    t2.join();
    return 0;
}
```

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Feel free to open issues and submit pull requests for any enhancements or bug fixes.

## Acknowledgements

Inspired by Serilog, LoggerCpp aims to bring a similar, easy-to-use logging experience to C++.

