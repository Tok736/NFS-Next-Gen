cmake_minimum_required(VERSION 3.9)
project(tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/inclide ${gmock_SOURCE_DIR})
include_directories(${INCLUDE_DIR})



file(GLOB_RECURSE TEST_CPPS "*/*.cpp")
add_executable(runTest test.cpp ${SOURCE_CPPS} ${TEST_CPPS} physics/physicsTest.cpp physics/physicsMock.h)

target_link_libraries(runTest gtest gtest_main gmock gmock_main)

find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(runTest sfml-graphics sfml-window sfml-system)
endif()

add_test(
        NAME runTest
        COMMAND runTest
)




