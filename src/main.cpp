#include "plotter_lib.h"
#include "implot_demo.h"

void imgui_init();
void plotter_draw();

Plotter plot("implot demo", 1920, 1080, &plotter_draw);

int main()
{

  if (!plot.Init())
  {
    return 1;
  }
  plot.Run();
  plot.Shutdown();
  return 0;
}

void imgui_init()
{
  ImGui::StyleColorsLight();
}

void plotter_draw()
{
  ImGui::SetNextWindowSize(plot.WindowSize());
  ImGui::Begin("Demo_LinePlots()"); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                                    // window size auto fit
  ImPlot::Demo_LinePlots();

  ImGui::End();

  // ImGui::Begin("Demo_MultipleAxes()");          // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
  // ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f)); // window size auto fit

  // ImPlot::Demo_MultipleAxes();
  // ImGui::End();

  // static bool show_debug_log = true;
  // static bool show_metrics = true;

  // ImGui::ShowDebugLogWindow(&show_debug_log);
  // ImGui::ShowMetricsWindow(&show_metrics);

  // ImPlot::ShowDemoWindow();
}