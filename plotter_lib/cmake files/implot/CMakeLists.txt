cmake_minimum_required(VERSION 3.1)

project(implot C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

set(SOURCE_FILES 
  ${CMAKE_CURRENT_SOURCE_DIR}/implot.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/implot_items.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/implot_demo.cpp
)

include_directories()

add_library(implot ${SOURCE_FILES})
target_link_libraries(implot imgui)
target_include_directories(implot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})