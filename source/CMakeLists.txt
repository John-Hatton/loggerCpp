# Find all .cpp files in the source directory
file(GLOB_RECURSE SOURCE_FILES "*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Indication to the code that this is a debug build
if (${IS_DEBUG_BUILD})
    set(CMAKE_CXX_FLAGS "-dDEBUG")
endif ()


# Link necessary libraries
#target_link_libraries(${PROJECT_NAME} PRIVATE )

set_target_properties(${PROJECT_NAME}  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


