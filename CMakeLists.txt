cmake_minimum_required(VERSION 3.16)

project(MySCPProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MySCPProject pubkeyauth.cpp)
target_link_options(MySCPProject PRIVATE -static -static-libgcc -static-libstdc++)