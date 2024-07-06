#ifndef CHART_H
#define CHART_H
#include <raylib.h>

int find_max(int *data, int point_count);
int find_min(int *data, int point_count);
double map(double input, double input_start, double input_end, double output_start, double output_end);

void draw_chart(int x,
                int y,
                int width,
                int height,
                const char *title,
                const char *yaxislabel,
                int xmin,
                int xmax,
                int ymin,
                int ymax,
                int *xdata,
                int *ydata,
                int points,
                Color linec);

void draw_chart_fit(int x,
                    int y,
                    int width,
                    int height,
                    const char *title,
                    const char *yaxislabel,
                    int *xdata,
                    int *ydata,
                    int points,
                    Color linec);

#endif // CHART_H