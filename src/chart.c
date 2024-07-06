
#include <raylib.h>
#include <stddef.h>
#include "chart.h"
#include <stdlib.h>
double map(double input, double input_start, double input_end, double output_start, double output_end)
{
    return output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
}

int find_min(int *data, int point_count)
{
    int min = __INT_MAX__;

    for (size_t i = 0; i < point_count; i++)
        if (data[i] < min)
            min = data[i];

    // if (min == __INT_MAX__)
    //     exit(0);

    return min;
}
int find_max(int *data, int point_count)
{
    int max = ~__INT_MAX__;

    for (size_t i = 0; i < point_count; i++)
        if (data[i] > max)
            max = data[i];

    // if (max == ~__INT_MAX__)
    //     exit(0);

    return max;
}

void draw_chart_fit(int x,
                    int y,
                    int width,
                    int height,
                    const char *title,
                    const char *yaxislabel,
                    int *xdata,
                    int *ydata,
                    int points,
                    Color linec)
{
    int xmin = find_min(xdata, points),
        xmax = find_max(xdata, points),
        ymin = find_min(ydata, points),
        ymax = find_max(ydata, points);

    draw_chart(x, y,
               width, height,
               title, yaxislabel,
               xmin, xmax, ymin, ymax,
               xdata, ydata, points, linec);
}

void draw_chart(
    int x, int y,
    int width,
    int height,
    const char *title,
    const char *yaxislabel,
    int xmin, int xmax,
    int ymin, int ymax,
    int *xdata,
    int *ydata,
    int points,
    Color linec)
{
    const int title_font_size = 12;
    const int axis_label_font_size = 12;

    int title_y = y + title_font_size / 2;
    int ylabellen = MeasureText(yaxislabel, axis_label_font_size);
    int title_sep_y = title_y + title_font_size + (title_font_size / 2);

    DrawText(title, (width / 2) - (MeasureText(title, title_font_size) / 2) + x, title_y, title_font_size, YELLOW);
    DrawTextPro(GetFontDefault(),
                yaxislabel,
                (Vector2){.x = x + axis_label_font_size, .y = y + (ylabellen / 2) + (height / 2)},
                (Vector2){.x = 0, .y = 0},
                90,
                axis_label_font_size, 1, YELLOW);

    DrawRectangleLines(x, y, width, height, LIGHTGRAY);
    DrawLine(x + (axis_label_font_size * 2), title_sep_y, x + width, title_sep_y, WHITE);
    DrawLine(x + (axis_label_font_size * 2), title_sep_y, x + (axis_label_font_size * 2), y + height, WHITE);

    int chartMinX = x + (axis_label_font_size * 2);
    int chartMinY = y + height;

    int chartMaxX = x + width;
    int chartMaxY = title_sep_y;

    // DrawCircle(chartMinX, chartMinY, 5, RED);
    // DrawCircle(chartMaxX, chartMaxY, 5, GREEN);

    // slope = (output_end - output_start) / (input_end - input_start)
    double xSlope = 1.0 * (chartMaxX - chartMinX) / (xmax - xmin);
    double ySlope = 1.0 * (chartMaxY - chartMinY) / (ymax - ymin);

    int last_x_pt, last_y_pt;
    bool first = true;

    for (int i = 0; i < points; i++)
    {
        int dataValuex = xdata[i];
        int dataValuey = ydata[i];

        // output = output_start + slope * (input - input_start)
        int scailedXValue = chartMinX + xSlope * (dataValuex - xmin);
        int scailedYValue = chartMinY + ySlope * (dataValuey - ymin);

        if (first)
        {
            first = false;
            last_x_pt = scailedXValue;
            last_y_pt = scailedYValue;
            continue;
        }

        if (!((scailedXValue > x + width) || (scailedYValue < title_sep_y)))
        {
            // DrawCircle(scailedXValue, scailedYValue, 5, RED);
            DrawLine(last_x_pt, last_y_pt, scailedXValue, scailedYValue, linec);
        }

        last_x_pt = scailedXValue;
        last_y_pt = scailedYValue;
    }
}
