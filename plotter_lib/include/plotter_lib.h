#ifndef __PLOTTER_LIB_H__
#define __PLOTTER_LIB_H__

#include "imgui.h"
#include "implot.h"

typedef void (*plotter_init_cb)();
typedef void (*plotter_draw_cb)();
typedef void (*plotter_close_cb)();

struct GLFWwindow;
struct window_context
{
  const char *title;
  int width, height;
  bool full_screen;
  GLFWwindow *window;
  ImVec4 clear_color;
  plotter_init_cb fn_init;
  plotter_draw_cb fn_draw;
  plotter_close_cb fn_close;
  ImPlotContext *implot_context;
};
class Plotter
{
public:
  Plotter(const char *title, int screen_width, int screen_height,
          plotter_draw_cb draw_func,
          plotter_init_cb init_func = 0,
          plotter_close_cb close_func = 0);
  bool Init();
  void Run();
  void Shutdown();

  ImVec2 WindowSize();

private:
  window_context m_Context;
};

#endif