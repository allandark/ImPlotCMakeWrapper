#ifndef __PLOTTER_LIB_H__
#define __PLOTTER_LIB_H__

#include "imgui.h"
#include "implot.h"

typedef void (*plotter_init_cb)();
typedef void (*plotter_draw_cb)();
typedef void (*plotter_close_cb)();

int InitPlotterInit(const char *title,
                    unsigned int screen_width,
                    unsigned int screen_height,
                    plotter_draw_cb draw_func,
                    plotter_init_cb init_func = 0,
                    plotter_close_cb close_func = 0);

#endif