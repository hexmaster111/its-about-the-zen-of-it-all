#include <raylib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    const int disp_width = 1024, disp_height = 700,
              square_size = 200;

    float circle_size = 20.0f;

    InitWindow(disp_width, disp_height, "Breath");
    SetTargetFPS(60);

    int x = disp_width / 2 - square_size / 2,
        y = disp_height / 2 - square_size / 2,
        state = 0,
        frame = 0;

    while (!WindowShouldClose())
    {
        int circle_center_x, circle_center_y;
        const char *words;
        switch (state)
        {
        case 0:
            circle_center_x = x;
            circle_center_y = (y + square_size) - frame;
            words = "Breath in";
            break;
        case 1:
            circle_center_x = x + frame;
            circle_center_y = y;
            words = "Hold";
            break;
        case 2:
            circle_center_x = x + square_size;
            circle_center_y = y + frame;
            words = "Breath Out";

            break;
        case 3:
            circle_center_x = x + square_size - frame;
            circle_center_y = y + square_size;
            words = "Hold";
            break;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleLines(x, y, square_size, square_size, LIGHTGRAY);
        DrawCircle(circle_center_x, circle_center_y, circle_size, WHITE);
        DrawText(words, x + square_size / 2 - MeasureText(words, 18) / 2, y + square_size / 2, 18, YELLOW);

        // debug
        // DrawText(TextFormat("Frame:%d", frame), 25, 25, 18, GREEN);
        // DrawText(TextFormat("State:%d", state), 25, 25 + 20, 18, GREEN);
        // DrawText(TextFormat("X:%d, Y:%d", circle_center_x, circle_center_y),
        //          25, 25 + 40, 18, GREEN);
        EndDrawing();

        if (++frame > square_size)
        {
            if (++state > 3)
                state = 0;

            frame = 0;
        }
    }

    CloseWindow();
}