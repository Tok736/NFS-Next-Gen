cmake_minimum_required(VERSION 3.16)
project(testAll)

set(CMAKE_CXX_STANDARD 14)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(testAll main.cpp physicsFunc.cpp)
target_link_libraries(testAll gtest Threads::Threads)
