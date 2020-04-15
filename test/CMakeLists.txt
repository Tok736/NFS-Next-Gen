cmake_minimum_required(VERSION 3.9)
project(tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE TEST_CPPS "*/*.cpp")
add_executable(runTest test.cpp ${SOURCE_CPPS} ${TEST_CPPS})

target_link_libraries(runTest gtest gtest_main)

add_test(
        NAME runTest
        COMMAND runTest
)