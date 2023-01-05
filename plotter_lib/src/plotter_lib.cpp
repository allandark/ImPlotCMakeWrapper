#include "plotter_lib.h"

#include <iostream>
#include <stdio.h>
#include <glfw/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "implot.h"
#include "implot_demo.h"

window_context context;

static void glfw_error_callback(int error, const char *description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

Plotter::Plotter(const char *title, int screen_width, int screen_height,
                 plotter_draw_cb draw_func,
                 plotter_init_cb init_func,
                 plotter_close_cb close_func)
{
  m_Context.title = title;
  m_Context.width = screen_width;
  m_Context.height = screen_height;
  m_Context.fn_init = init_func;
  m_Context.fn_draw = draw_func;
  m_Context.fn_close = close_func;
  m_Context.clear_color.x = m_Context.clear_color.y = m_Context.clear_color.z = 0.2f;
  m_Context.clear_color.w = 1.00f;
}
bool Plotter::Init()
{
  m_ShouldClose = false;
  // Setup window
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return false;

  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // Create window with graphics context
  m_Context.window = glfwCreateWindow(m_Context.width, m_Context.height, m_Context.title, NULL, NULL);
  if (m_Context.window == NULL)
    return false;
  glfwMakeContextCurrent(m_Context.window);
  glfwSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(m_Context.window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  m_Context.implot_context = ImPlot::CreateContext();
  if (m_Context.fn_init)
  {
    m_Context.fn_init();
  }
  else
  {
    // Default initialization
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
  }

  return true;
}
bool Plotter::Update()
{
  // Main loop

  m_ShouldClose = glfwWindowShouldClose(m_Context.window);
  // Poll and handle events (inputs, window resize, etc.)
  // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
  // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
  // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
  // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
  glfwPollEvents();

  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  m_Context.fn_draw();

  // Rendering

  ImGui::Render();
  glfwGetFramebufferSize(m_Context.window, &m_Context.width, &m_Context.height);
  glViewport(0, 0, m_Context.width, m_Context.height);
  glClearColor(m_Context.clear_color.x * m_Context.clear_color.w,
               m_Context.clear_color.y * m_Context.clear_color.w,
               m_Context.clear_color.z * m_Context.clear_color.w,
               m_Context.clear_color.w);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(m_Context.window);

  return m_ShouldClose;
}
void Plotter::Shutdown()
{
  if (m_Context.fn_close)
  {
    m_Context.fn_close();
  }
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(m_Context.window);
  glfwTerminate();
}

ImVec2 Plotter::WindowSize()
{
  return ImVec2((float)m_Context.width, (float)m_Context.height);
}
