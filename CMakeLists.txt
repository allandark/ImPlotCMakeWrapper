cmake_minimum_required(VERSION 3.1)

project(demo VERSION 0.1 LANGUAGES CXX)

add_subdirectory(plotter_lib)

set(SOURCE_FILES src/main.cpp)

include_directories(demo plotter_lib/include)

add_executable(demo ${SOURCE_FILES})

target_link_libraries(demo plotter-lib)
