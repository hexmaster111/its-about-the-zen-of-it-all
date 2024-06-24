
#include <raylib.h>
#include <stdio.h>
#include "chart.h"

void draw_chart(
    int x, int y,
    int width,
    int height,
    int xmin,
    int xmax,
    int ymin,
    int ymax,
    int *xdata,
    int *ydata,
    int points)
{
    DrawRectangleLines(x, y, width, height, LIGHTGRAY);
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

    while (!WindowShouldClose())
    {

        BeginDrawing();
        ClearBackground(BLACK);

        int xdata[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        int ydata[] = {1, 2, 3, 4, 5, 4, 3, 2, 1, 0};
        draw_chart(10, 10, disp_width - 20, disp_height - 20, -10, 10, -5, 5, xdata, ydata, 10);
        EndDrawing();
    }

    CloseWindow();
}