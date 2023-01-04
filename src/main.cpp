#include "plotter_lib.h"
#include "implot_demo.h"

void imgui_init()
{
  ImGui::StyleColorsLight();
}

void imgui_draw()
{

  ImGui::Begin("Demo_LinePlots()");             // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
  ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f)); // window size auto fit
  ImPlot::Demo_LinePlots();

  ImGui::End();

  ImGui::Begin("Demo_MultipleAxes()");          // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
  ImGui::SetNextWindowSize(ImVec2(0.0f, 0.0f)); // window size auto fit

  ImPlot::Demo_MultipleAxes();
  ImGui::End();

  static bool show_debug_log = true;
  static bool show_metrics = true;

  ImGui::ShowDebugLogWindow(&show_debug_log);
  ImGui::ShowMetricsWindow(&show_metrics);
}

int main()
{
  InitPlotterInit("window title", 800, 600, &imgui_draw /*, &imgui_init*/);
  return 0;
}