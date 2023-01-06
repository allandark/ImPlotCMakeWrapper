cmake_minimum_required(VERSION 3.1)

project(plotter-lib VERSION 0.1 LANGUAGES CXX)

find_package(OpenGL REQUIRED)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)
add_subdirectory(imgui)
add_subdirectory(implot)

set(SOURCE_FILES 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/plotter_lib.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/implot_demo.cpp
)
set(LIBS glfw ${GLFW_LIBRARIES} imgui implot  OpenGL::GL)
set(PLATFORM_LIBS)
if (UNIX)
  # Unix platform
  set(PLATFORM_LIBS )
elseif(MSVC)
  # Windows platform
  set(PLATFORM_LIBS gdi32.lib shell32.lib)
endif (UNIX)



set(INCLUDE_DIRS 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
  ${CMAKE_CURRENT_SOURCE_DIR}/implot
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui
  #${CMAKE_CURRENT_SOURCE_DIR}/src
  #${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
)

include_directories(plotter-lib ${INCLUDE_DIRS})

add_library(plotter-lib ${SOURCE_FILES})
target_link_libraries(plotter-lib ${PLATFORM_LIBS} ${LIBS})
target_include_directories(plotter-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/implot ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
