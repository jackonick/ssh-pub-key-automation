cmake_minimum_required(VERSION 3.16)

project(MySCPProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(
    ${CMAKE_SOURCE_DIR}/computer_list.txt
    ${CMAKE_BINARY_DIR}/computer_list.txt
    COPYONLY
)


enable_testing()

include(FetchContent)

# -------------------------
# GoogleTest
# -------------------------
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

# Prevent overriding parent project compiler settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(MySCPProject
    pubkeyauth.cpp
)

# -------------------------
# Test Executable Target
# -------------------------
add_executable(MySCPProject_Tests
    tests.cpp
    pubkeyauth.cpp
)

target_link_libraries(MySCPProject_Tests
    PRIVATE
    gtest_main
)

target_compile_definitions(MySCPProject_Tests
    PRIVATE
    UNIT_TESTING
)


# -------------------------
# GoogleTest discovery
# -------------------------
include(GoogleTest)
gtest_discover_tests(MySCPProject_Tests)
