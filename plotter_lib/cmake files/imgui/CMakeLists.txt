cmake_minimum_required(VERSION 3.1)

project(imgui C CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

set(SOURCE_FILES 
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui_demo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui_draw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui_tables.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui_widgets.cpp
)

add_library(imgui ${SOURCE_FILES})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})