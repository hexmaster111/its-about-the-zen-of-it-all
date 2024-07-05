#include <stdio.h>

#include <raylib.h>
#include "chart.h"

int main(int argc, char *argv[])
{
    const int disp_width = 1024,
              disp_height = 700;

    InitWindow(disp_width, disp_height, "Chart Demo");
    SetTargetFPS(60);

#define pt_count 1000
    int xdata[pt_count] = {0};
    int ydata[pt_count] = {0};

    for (int i = 0; i < pt_count; i++)
    {
        xdata[i] = i;
        ydata[i] = (i + 1) / 2;
    }

    int chartX = 10, chartY = 10, chartW = 200;
#define movespeed 5

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyDown(KEY_RIGHT))
            chartX += movespeed;

        if (IsKeyDown(KEY_LEFT))
            chartX -= movespeed;

        if (IsKeyDown(KEY_UP))
            chartY -= movespeed;

        if (IsKeyDown(KEY_DOWN))
            chartY += movespeed;

        if (IsKeyDown(KEY_KP_ADD))
            chartW += movespeed;

        if (IsKeyDown(KEY_KP_SUBTRACT))
            chartW -= movespeed;

        // draw_chart(/*x*/ chartX,
        //            /*x*/ chartY,
        //            /*w*/ chartW,
        //            /*h*/ 200,
        //            /*title*/ "Test Chart!",
        //            /*y axis title*/ "Barks",
        //            /*x min*/ -2,
        //            /*x max*/ 1000,
        //            /*y min*/ -2,
        //            /*y max*/ 150,
        //            xdata, ydata, pt_count);

        draw_chart_fit(/*x*/ chartX,
                       /*x*/ chartY,
                       /*w*/ chartW,
                       /*h*/ 200,
                       /*title*/ "Test Chart!",
                       /*y axis title*/ "Barks",
                       xdata, ydata, pt_count, YELLOW);

        EndDrawing();
    }

    CloseWindow();
}