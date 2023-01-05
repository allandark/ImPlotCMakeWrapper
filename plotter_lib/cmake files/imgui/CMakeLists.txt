cmake_minimum_required(VERSION 3.1)

project(imgui VERSION 0.1 LANGUAGES CXX)


set(SOURCE_FILES 
  imgui.cpp 
  imgui_draw.cpp
  imgui_demo.cpp 
  imgui_tables.cpp
  imgui_widgets.cpp
)

set(TARGET_INCLUDE_DIRS 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/backends
)



add_library(imgui ${SOURCE_FILES})

target_include_directories(imgui PUBLIC ${TARGET_INCLUDE_DIRS})