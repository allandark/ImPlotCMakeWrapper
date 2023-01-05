cmake_minimum_required(VERSION 3.1)

project(implot VERSION 0.1 LANGUAGES CXX)

set(SOURCE_FILES  
  implot_items.cpp
  implot.cpp 
)

include_directories(implot ${CMAKE_CURRENT_SOURCE_DIR}/../imgui)

add_library(implot ${SOURCE_FILES})
target_include_directories(implot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(implot imgui)