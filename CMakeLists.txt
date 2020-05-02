cmake_minimum_required(VERSION 3.15.3)
project(testAll)

set(CMAKE_CXX_STANDARD 14)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(testAll main.cpp physicsFunc.cpp graphicsFunc.cpp)

target_link_libraries(testAll sfml-graphics sfml-audio)
target_link_libraries(testAll gtest Threads::Threads)





