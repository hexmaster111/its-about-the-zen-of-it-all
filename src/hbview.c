#include <raylib.h>
#include <stdio.h>
#include "heart_rate_repeter_com.h"
#include "chart.h"

int main(int argc, char *argv[])
{
    hrr_init();
    if (!hrr_open("/dev/cu.usbmodem101"))
    {
        return -1;
    }

    const int disp_width = 1024,
              disp_height = 700;

    InitWindow(disp_width, disp_height, "Chart Demo");
    SetTargetFPS(60);

    unsigned long data = 0, frames = 0;
#define DATA_PTS 100
    int RD[DATA_PTS] = {0},
        ID[DATA_PTS] = {0},
        x[DATA_PTS],
        rdnow,
        idnow;

    for (size_t i = 0; i < DATA_PTS; i++)
        x[i] = i;

    bool noData = true;
    int rdidx = 0, ididx = 0;
    int heartRate = 0;
    float tempature = 0;

    while (!WindowShouldClose())
    {
        enum MESSAGE_t msg;
        float fv = -1;
        int iv = -1;
        long lv = -1;
        if (hrr_read(&msg, &fv, &iv, &lv))
        {
            data++;

            if (msg == MESSAGE_ID)
            {
                idnow = ID[ididx] = lv;
                ididx++;

                if (ididx > DATA_PTS)
                    ididx = 0;
            }

            if (msg == MESSAGE_RD)
            {
                rdnow = RD[rdidx] = lv;
                rdidx++;

                if (rdidx > DATA_PTS)
                    rdidx = 0;
            }

            if (msg == MESSAGE_TP)
            {
                tempature = fv;
            }

            if (msg == MESSAGE_HR)
            {
                noData = false;
                heartRate = iv;
            }

            if (msg == MESSAGE_ND)
            {
                noData = true;
                heartRate = 0;
            }
        }
        else
        {
            frames++;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(0, 0);

        DrawText(TextFormat("F %ld", frames), 10, 20, 12, WHITE);
        DrawText(TextFormat("D %ld", data), 10, 32, 12, WHITE);
        DrawText(TextFormat("id %ld rd %ld", idnow, rdnow), 10, 44, 12, WHITE);
        DrawText(TextFormat("%.2ff", tempature), 250, 265, 15, YELLOW);

        if (!noData)
        {
            const char *vitalsmessage = TextFormat("Heart Rate %d bpm\n", heartRate);
            DrawText(vitalsmessage, 250, 250, 15, YELLOW);
        }

        // + 1 and -1 for the umm chart to look right... idk why, but the first datapoint is zero alot?!
        draw_chart_fit(350, 100, 600, 400, "Red Data               ", "", x, RD + 1, DATA_PTS - 1, RED);
        draw_chart_fit(350, 100, 600, 400, "                IR Data", "", x, ID, DATA_PTS, PURPLE);

        EndDrawing();
    }

    CloseWindow();
    hrr_close();
}