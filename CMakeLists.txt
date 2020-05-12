cmake_minimum_required(VERSION 3.15.3)
project(testAll)

set(CMAKE_CXX_STANDARD 14)
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(testAll main.cpp physicsFunc.cpp graphicsFunc.cpp logic/ClientState.cpp logic/ServerState.cpp logic/MapGenerator.cpp logic/Game.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(testAll ${SFML_LIBRARIES})
endif()

target_link_libraries(testAll gtest Threads::Threads)





