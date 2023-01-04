cmake_minimum_required(VERSION 3.1)

project(plotter-lib VERSION 0.1 LANGUAGES CXX)


add_subdirectory(glfw)
add_subdirectory(imgui)
add_subdirectory(implot)

set(SOURCE_FILES 
  ${CMAKE_CURRENT_SOURCE_DIR}/src/plotter_lib.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/implot_demo.cpp
)
set(LIBS glfw ${GLFW_LIBRARIES} imgui implot)
set(PLATFORM_LIBS)
if (UNIX)
  # Unix platform
  set(PLATFORM_LIBS GL)
elseif(MSVC)
  # Windows platform
  set(PLATFORM_LIBS opengl32.lib gdi32.lib shell32.lib)
endif (UNIX)



set(INCLUDE_DIRS 
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
  ${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/implot
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include_directories(plotter-lib ${INCLUDE_DIRS})

add_library(plotter-lib ${SOURCE_FILES})
target_link_libraries(plotter-lib ${PLATFORM_LIBS} ${LIBS})
target_include_directories(plotter-lib PUBLIC ${INCLUDE_DIRS})
