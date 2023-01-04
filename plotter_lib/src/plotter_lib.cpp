#include "plotter_lib.h"

#include <iostream>
#include <stdio.h>
#include <glfw/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "implot.h"
#include "implot_demo.h"

struct window_context
{
  const char *title;
  unsigned int width, height;
  bool full_screen;
  GLFWwindow *window;
  plotter_init_cb fn_init;
  plotter_draw_cb fn_draw;
  plotter_close_cb fn_close;
  ImPlotContext *implot_context;
};

window_context context;

static void glfw_error_callback(int error, const char *description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int InitPlotterInit(const char *title, unsigned int screen_width, unsigned int screen_height, plotter_draw_cb draw_func, plotter_init_cb init_func, plotter_close_cb close_func)
{
  context.title = title;
  context.width = screen_width;
  context.height = screen_height;
  context.fn_init = init_func;
  context.fn_draw = draw_func;
  context.fn_close = close_func;
  // Setup window
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;

  // GL 3.0 + GLSL 130
  const char *glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // Create window with graphics context
  context.window = glfwCreateWindow(screen_width, screen_height, title, NULL, NULL);
  if (context.window == NULL)
    return 1;
  glfwMakeContextCurrent(context.window);
  glfwSwapInterval(1); // Enable vsync

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(context.window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);
  context.implot_context = ImPlot::CreateContext();
  if (context.fn_init)
  {
    context.fn_init();
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

  // Our state
  bool show_demo_window = true;
  bool show_another_window = true;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Main loop
  while (!glfwWindowShouldClose(context.window))
  {
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

    context.fn_draw();

    // Rendering

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(context.window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(context.window);
  }

  if (context.fn_close)
  {
    context.fn_close();
  }
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(context.window);
  glfwTerminate();

  return 0;
}
