cmake_minimum_required(VERSION 3.17)
project(isometric)

set(CMAKE_CXX_STANDARD 14)

set(USE_VCPKG OFF)
if (WIN32)
    set(USE_VCPKG ON)
endif()

add_executable(isometric main.cpp)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

find_package(raylib CONFIG REQUIRED)
target_include_directories(isometric PRIVATE ${raylib_INCLUDE_DIRS})

if (USE_VCPKG)
    target_link_libraries(isometric PRIVATE ${raylib_LIBRARIES})
else()
    target_link_libraries(isometric PRIVATE $ENV{lib_path}/raylib/lib/libraylib.so)
endif()
