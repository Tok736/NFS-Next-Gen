cmake_minimum_required(VERSION 3.9)
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

# ==== Linking with cpp math library ==== #
target_link_libraries(${PROJECT_NAME} m)

# ==== Linking with Boost ==== #
find_package(Boost REQUIRED COMPONENTS system filesystem date_time thread)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})


# ==== Linking with Google test ==== #
enable_testing()

add_subdirectory(${LIBRARIES_DIR}/googletest)
add_subdirectory(test)

include_directories(${LIBRARIES_DIR}/googletest/googletest/include)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)

include_directories(${LIBRARIES_DIR}/googletest/googlemock/include)
target_link_libraries(${PROJECT_NAME} gmock gmock_main)


# ==== Linking with SQLite DataBase ==== #
# Look for the necessary header
find_path(SQLite3_INCLUDE_DIR NAMES sqlite3.h)
mark_as_advanced(SQLite3_INCLUDE_DIR)

# Look for the necessary library
find_library(SQLite3_LIBRARY NAMES sqlite3 sqlite)
mark_as_advanced(SQLite3_LIBRARY)

# Extract version information from the header file
if(SQLite3_INCLUDE_DIR)
    file(STRINGS ${SQLite3_INCLUDE_DIR}/sqlite3.h _ver_line
            REGEX "^#define SQLITE_VERSION  *\"[0-9]+\\.[0-9]+\\.[0-9]+\""
            LIMIT_COUNT 1)
    string(REGEX MATCH "[0-9]+\\.[0-9]+\\.[0-9]+"
            SQLite3_VERSION "${_ver_line}")
    unset(_ver_line)
endif()

find_package_handle_standard_args(SQLite3
        REQUIRED_VARS SQLite3_INCLUDE_DIR SQLite3_LIBRARY
        VERSION_VAR SQLite3_VERSION)

# Create the imported target
if(SQLite3_FOUND)
    set(SQLite3_INCLUDE_DIRS ${SQLite3_INCLUDE_DIR})
    set(SQLite3_LIBRARIES ${SQLite3_LIBRARY})
    if(NOT TARGET SQLite::SQLite3)
        add_library(SQLite::SQLite3 UNKNOWN IMPORTED)
        set_target_properties(SQLite::SQLite3 PROPERTIES
                IMPORTED_LOCATION             "${SQLite3_LIBRARY}"
                INTERFACE_INCLUDE_DIRECTORIES "${SQLite3_INCLUDE_DIR}")
    endif()
endif()

if (SQLITE3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
    target_link_libraries (${PROJECT_NAME} ${SQLite3_LIBRARIES})
endif (SQLITE3_FOUND)


