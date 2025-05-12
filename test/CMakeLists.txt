cmake_minimum_required(VERSION 3.10)
project(TetrisTests)

enable_testing()

include_directories("../include")

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
link_libraries(${GTEST_LIBRARIES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GMOCK REQUIRED gmock)
include_directories(${GMOCK_INCLUDE_DIRS})
link_libraries(${GMOCK_LIBRARIES})


add_executable(tetris_tests brick_test.cpp) 

target_link_libraries(tetris_tests ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} pthread)

add_test(NAME TetrisTest COMMAND tetris_tests)
