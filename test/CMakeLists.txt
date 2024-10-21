project(Google_Tests)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

set(SOURCES
    ../source/LogMessage.cpp
    ../source/Sink/ConsoleSink.cpp
    ../source/Sink/FileSink.cpp
    ../source/Logger.cpp
)

add_executable(loggerCpp_Tests
        ${SOURCE_FILES} ${SOURCES}
)

target_link_libraries(loggerCpp_Tests gtest gtest_main gmock )

#
##
#
########
#
##
#

###################
#					#
#    Google Test	#
#					#
###################



include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#
##
#
########
#
##
#