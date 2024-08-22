cmake_minimum_required(VERSION 3.0)

project(tetris)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(tetris ${SOURCES})


find_package(Threads REQUIRED)
target_link_libraries(tetris ncurses ${CMAKE_THREAD_LIBS_INIT})