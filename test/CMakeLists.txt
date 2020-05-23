cmake_minimum_required(VERSION 3.9)
project(tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories(${INCLUDE_DIR})

file(GLOB_RECURSE TEST_CPPS "*/*.cpp")
add_library(SQLite STATIC ../src/physics/SQLite.cpp)
#add_executable(runTest test.cpp collision/collisionNaive.cpp ${TEST_CPPS})

#set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake_modules")
#find_package(SQLite3)
#if (SQLite3_FOUND)
#    include_directories(${SQLite3_INCLUDE_DIRS})
#    target_link_libraries (SQLite ${SQLite3_LIBRARIES})
#endif (SQLite3_FOUND)
#
#target_link_libraries(runTest gtest gtest_main gmock gmock_main SQLite)
#add_test(
#        NAME runTest
#        COMMAND runTest
#)
