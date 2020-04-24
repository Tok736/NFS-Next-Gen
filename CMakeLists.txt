cmake_minimum_required(VERSION 3.16)
set(PROJECT_NAME NFS_Next_Gen)
project(${PROJECT_NAME} CXX)

# ==== Standard and flags ==== #
set(GCC_COVERAGE_COMPILE_FLAGS "-lboost_system -lboost_thread")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "-lm -Wno-unknown-pragmas -Wall -Wextra -Werror -fprofile-arcs -ftest-coverage -lgcov")
set(CMAKE_EXE_LINKER_FLAGS "-lgcov --coverage")

# ==== Main directories ==== #
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(LIBRARIES_DIR ${PROJECT_SOURCE_DIR}/libs)

# ==== Need for running main.cpp ==== #
include_directories(${INCLUDE_DIR})
file(GLOB_RECURSE SOURCE_CPPS ${SOURCE_DIR}/*/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_CPPS} ${SOURCE_DIR}/main.cpp)

# ==== Linking with SQLite3 dataBase ==== #





find_package(SQLite3 REQUIRED)

if (SQLITE3_FOUND)
    include_directories(${SQLITE3_INCLUDE_DIRS})
    target_link_libraries (${PROJECT_NAME} ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)
