
#include <raylib.h>
#include <stdio.h>
#include "chart.h"

int map(int input, int input_start, int input_end, int output_start, int output_end)
{
    return output_start + ((output_end - output_start) / (input_end - input_start)) * (input - input_start);
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
    int points)
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

    for (int i = 0; i < points; i++)
    {
        int dataValuex = xdata[i];
        int dataValuey = ydata[i];

        // output = output_start + slope * (input - input_start)
        int scailedXValue = chartMinX + xSlope * (dataValuex - xmin);
        int scailedYValue = chartMinY + ySlope * (dataValuey - ymin);

        DrawCircle(scailedXValue, scailedYValue, 2, YELLOW);
    }
}

int main(int argc, char *argv[])
{
    const int disp_width = 1024,
              disp_height = 700;

    InitWindow(disp_width, disp_height, "Chart Demo");
    SetTargetFPS(60);

    int rect_width = 400,
        rect_heigh = 200,
        x = disp_width / 2 - rect_width / 2,
        y = disp_height / 2 - rect_heigh / 2;

    int xdata[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int ydata[] = {1, 2, 3, 4, 5, 4, 3, 2, 1, 0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_chart(/*x*/ 10,
                   /*x*/ 10,
                   /*w*/ 200,
                   /*h*/ 200,
                   /*title*/ "Test Chart!",
                   /*y axis title*/ "Barks",
                   /*x min*/ -2,
                   /*x max*/ 15,
                   /*y min*/ -2,
                   /*y max*/ 15,
                   xdata, ydata, 10);
        EndDrawing();
    }

    CloseWindow();
}