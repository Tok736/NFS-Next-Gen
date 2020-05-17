cmake_minimum_required(VERSION 3.9)
project(tests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
include_directories("${CMAKE_CURRENT_LIST_DIR}/dataBase")


set(CMAKE_CURRENT_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}")

#file(GLOB_RECURSE TEST_CPPS "*/*.cpp")
add_library(SQLite STATIC ../src/SQLite.cpp)
add_executable(runTest test.cpp dataBase/dataBaseTest.cpp ${TEST_CPPS})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake_modules")
find_package(SQLITE3)
if (SQLITE3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
    target_link_libraries (SQLite ${SQLite3_LIBRARIES})
endif (SQLITE3_FOUND)

target_link_libraries(runTest gtest gtest_main gmock gmock_main SQLite)

add_test(
        NAME runTest
        COMMAND runTest
)
