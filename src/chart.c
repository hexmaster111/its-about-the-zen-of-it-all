
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
    int xmin,
    int xmax,
    int ymin,
    int ymax,
    int *xdata,
    int *ydata,
    int points)
{
    const int title_font_size = 12;
    const int axis_label_font_size = 12;

    int title_y = y + title_font_size / 2;

    DrawRectangleLines(x, y, width, height, LIGHTGRAY);
    DrawText(title, (width / 2) - (MeasureText(title, title_font_size) / 2) + x, title_y, title_font_size, YELLOW);
    // Axis labels are tipped sideways

    int title_sep_y = title_y + title_font_size + (title_font_size / 2);
    // DrawTextPro(GetFontDefault(), yaxislabel, (Vector2){.x = 0, .y = 0}, (Vector2){.x = 0, .y = 0}, 90, axis_label_font_size, )

    DrawLine(x + axis_label_font_size + (axis_label_font_size / 2), title_sep_y, x + width, title_sep_y, WHITE);
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
    int padding = 200;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        draw_chart(padding, padding,
                   disp_width - padding * 2,
                   disp_height - padding * 2,
                   "Test Chart!",
                   "Barks",
                   -10, 10,
                   -5, 5,
                   xdata, ydata, 10);
        EndDrawing();
    }

    CloseWindow();
}