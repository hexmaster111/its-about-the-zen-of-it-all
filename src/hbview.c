#include <raylib.h>
#include <stdio.h>
#include "heart_rate_repeter_com.h"
#include "chart.h"

int main(int argc, char *argv[])
{

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
        x[DATA_PTS];

    for (size_t i = 0; i < DATA_PTS; i++)
        x[i] = i;

    bool noData = true;
    int rdidx = 0, ididx = 0;
    int heartRate = 0;

    while (!WindowShouldClose())
    {
        enum MESSAGE_t msg;
        float fv = -1;
        int iv = -1;
        long lv = -1;
        if (hrr_read(&msg, &fv, &iv, &lv))
        {
            data++;
            if (!(msg == MESSAGE_ID || msg == MESSAGE_RD))
                fprintf(stdout, "got! %d %d %f %ld \n", (int)msg, iv, fv, lv);

            if (msg == MESSAGE_ID)
            {
                ID[ididx] = lv;
                ididx++;

                if (ididx > DATA_PTS)
                    ididx = 0;
            }

            if (msg == MESSAGE_RD)
            {
                RD[rdidx] = lv;
                rdidx++;

                if (rdidx > DATA_PTS)
                    rdidx = 0;
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

        const char *vitalsmessage = "DATA NOT READY";

        if (!noData)
        {
            vitalsmessage = TextFormat("Heart Rate %d bpm\n", heartRate);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(0, 0);
        DrawText(TextFormat("F %ld", frames), 10, 20, 12, WHITE);
        DrawText(TextFormat("D %ld", data), 10, 32, 12, WHITE);
        draw_chart_fit(50, 50, 300, 200, "IR Data", "", x, ID, DATA_PTS);
        draw_chart_fit(355, 50, 300, 200, "Red Data", "", x, RD, DATA_PTS);
        DrawText(vitalsmessage, 250, 250, 15, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    hrr_close();
}