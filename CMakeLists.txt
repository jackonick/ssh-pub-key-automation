cmake_minimum_required(VERSION 3.16)

project(MySCPProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Prevent overriding parent project compiler settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 1. Main Application Target
add_executable(MySCPProject pubkeyauth.cpp)
target_link_options(MySCPProject PRIVATE -static -static-libgcc -static-libstdc++)

# 2. Test Executable Target (Make sure test.cpp and pubkeyauth.cpp are listed here)
add_executable(MySCPProject_Tests tests.cpp pubkeyauth.cpp)
target_link_libraries(MySCPProject_Tests PRIVATE gtest_main)
target_link_options(MySCPProject_Tests PRIVATE -static -static-libgcc -static-libstdc++)
target_compile_definitions(MySCPProject_Tests PRIVATE UNIT_TESTING)
include(GoogleTest)
gtest_discover_tests(MySCPProject_Tests)