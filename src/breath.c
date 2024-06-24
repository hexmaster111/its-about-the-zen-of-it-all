#include <raylib.h>
#include <stdio.h>
#include "heart_rate_repeter_com.h"

int main(int argc, char **argv)
{
    const int disp_width = 1024,
              disp_height = 700,
              font_size = 60;

    if (!hrr_open("/dev/ttyACM0"))
    {
        return -1;
    }

    while (1)
    {
        enum MESSAGE_t msg;
        float fv = -1;
        int iv = -1;
        long lv = -1;
        if (hrr_read(&msg, &fv, &iv, &lv))
        {
            if (msg == MESSAGE_ID ||
                msg == MESSAGE_RD)
                continue;
            fprintf(stdout, "got! %d %d %f %ld \n", (int)msg, iv, fv, lv);
        }
    }

    InitWindow(disp_width, disp_height, "Breath");
    SetTargetFPS(60);

    int rect_width = 400,
        rect_heigh = 200,
        x = disp_width / 2 - rect_width / 2,
        y = disp_height / 2 - rect_heigh / 2,
        state = 0,
        frame = 0;

    float circle_size = 20.0f;

    while (!WindowShouldClose())
    {
        int circle_center_x, circle_center_y, side_len;
        const char *words;
        switch (state)
        {
        case 0:
            words = "Breath in";
            side_len = rect_heigh;
            circle_center_x = x;
            circle_center_y = (y + rect_heigh) - frame;
            break;

        case 1:
            words = "Hold";
            side_len = rect_width;
            circle_center_x = x + frame;
            circle_center_y = y;
            break;

        case 2:
            words = "Breath Out";
            side_len = rect_heigh;
            circle_center_x = x + rect_width;
            circle_center_y = y + frame;
            break;

        case 3:
            words = "Hold";
            side_len = rect_width;
            circle_center_x = x + rect_width - frame;
            circle_center_y = y + rect_heigh;
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleLines(x, y, rect_width, rect_heigh, LIGHTGRAY);
        DrawCircle(circle_center_x, circle_center_y, circle_size, LIGHTGRAY);
        DrawText(words, x + rect_width / 2 - MeasureText(words, font_size) / 2,
                 (y + rect_heigh / 2) - font_size / 2, font_size, YELLOW);
        EndDrawing();

        if (++frame > side_len)
        {
            frame = 0;
            if (++state > 3)
                state = 0;
        }
    }

    CloseWindow();
    hrr_close();
}