cmake_minimum_required(VERSION 3.17)
project(isometric)

set(CMAKE_CXX_STANDARD 14)

add_executable(isometric main.cpp)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(raylib CONFIG REQUIRED)
target_include_directories(isometric PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(isometric PRIVATE ${raylib_LIBRARIES})