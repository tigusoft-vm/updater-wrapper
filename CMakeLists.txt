cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(a a.cpp)
add_executable(b b.cpp)
add_executable(c c.cpp)

target_link_libraries(b boost_system boost_filesystem)