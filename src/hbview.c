#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "heart_rate_repeter_com.h"
#include "chart.h"

#define CP_COUNT (10)
int cp[CP_COUNT] = {0};

void CheckPaulse(int points, int in_ir_data[points], int ___[points], bool *out_isPaulse)
{
    for (int k = CP_COUNT; k > 0; k--)
    {
        cp[k] = cp[k - 1];
    }

    int min, max;
    cp[0] = map(in_ir_data[0],
                min = find_min(in_ir_data, points),
                max = find_max(in_ir_data, points),
                0, 1000);

    printf("nv:%d min:%d max:%d in:%d\n", cp[0], min, max, in_ir_data[0]);
    *out_isPaulse = (cp[0] > 600);
}

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
#define DATA_PTS 25
    int rd[DATA_PTS] = {0}, id[DATA_PTS] = {0},
        x[DATA_PTS],
        rdnow, idnow;

    for (size_t i = 0; i < DATA_PTS; i++)
        x[i] = i;

    bool noData = true, isFingerIn = false, isPaulse = false, lastPaulseState = false;
    int heartRate_fromSensor = 0,
        heartRate_fromCounting = 0,
        heartRate_fromExtrapolatingPaulseTimes = 0,
        countingCountedThisMinute = 0,
        activeScreen = 0;
    float tempature = 0;
    double lastHbCheck = GetTime(),
           timerCoutingPaulsesTime = GetTime();

    while (!WindowShouldClose())
    {
        enum MESSAGE_t msg;
        float fv = -1;
        int iv = -1;
        long lv = -1;
        while (hrr_read(&msg, &fv, &iv, &lv))
        {
            data++;

            if (msg == MESSAGE_ID)
            {

                for (int k = DATA_PTS; k > 0; k--)
                {
                    id[k] = id[k - 1];
                }

                idnow = id[0] = lv;
                CheckPaulse(DATA_PTS, rd, id, &isPaulse);

                if (isPaulse && !lastPaulseState)
                {
                    // state change into us finding a paulse! how fun
                    countingCountedThisMinute++;
                    double now = GetTime();

                    double perod = now - lastHbCheck;

                    heartRate_fromExtrapolatingPaulseTimes = (1.0 / perod) * 60;

                    // --
                    lastHbCheck = GetTime();
                    lastPaulseState = true;
                }

                if (!isPaulse && lastPaulseState)
                {
                    // state change into us done finding this pause!
                    lastPaulseState = false;
                }

                if (GetTime() - timerCoutingPaulsesTime > 15)
                {
                    heartRate_fromCounting = countingCountedThisMinute * 4;
                    countingCountedThisMinute = 0;
                    timerCoutingPaulsesTime = GetTime();
                }
            }

            if (msg == MESSAGE_RD)
            {

                for (int k = DATA_PTS; k > 0; k--)
                {
                    rd[k] = rd[k - 1];
                }

                rdnow = rd[0] = lv;
            }

            if (msg == MESSAGE_TP)
            {
                tempature = fv;
            }

            if (msg == MESSAGE_HR)
            {
                noData = false;
                heartRate_fromSensor = iv;
            }

            if (msg == MESSAGE_ND)
            {
                noData = true;
                heartRate_fromSensor = 0;
            }

            if (rdnow > 200000 && idnow > 600000)
                isFingerIn = true;
            else
                isFingerIn = false;
        }

        if (!isFingerIn)
        {

            for (size_t i = 0; i < DATA_PTS; i++)
                rd[i] = 0;

            for (size_t i = 0; i < DATA_PTS; i++)
                id[i] = 0;
        }

        if (IsKeyDown(KEY_ONE))
            activeScreen = 0;
        if (IsKeyDown(KEY_TWO))
            activeScreen = 1;

        // DRAWING STARTING

        frames++;
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(0, 0);

        if (activeScreen == 0)
        {

            DrawText(TextFormat("F %ld", frames), 10, 20, 12, WHITE);
            DrawText(TextFormat("D %ld", data), 10, 32, 12, WHITE);
            DrawText(TextFormat("id %d rd %d", idnow, rdnow), 10, 44, 12, WHITE);
            DrawText(TextFormat("last hb time %f", lastHbCheck), 10, 66, 12, WHITE);
            DrawText(TextFormat("hp from sensr: %d", heartRate_fromSensor), 10, 78, 12, WHITE);
            DrawText(TextFormat("hp from count: %d", heartRate_fromCounting), 10, 90, 12, WHITE);
            DrawText(TextFormat("dgb: %f", GetTime() - timerCoutingPaulsesTime), 10, 102, 12, WHITE);

            if (!isFingerIn)
            {
                DrawText("FINGER OUT", 500, 200, 24, WHITE);
            }

            if (isFingerIn)
            {
                DrawText(TextFormat("%d", heartRate_fromExtrapolatingPaulseTimes), 250, 500, 48, YELLOW);
                DrawText("    bpm", 250, 500, 48, YELLOW);
                DrawText(TextFormat("%.2ff", tempature), 350, 500, 15, YELLOW);
            }
            else
            {
                DrawText("--- bpm", 250, 500, 48, YELLOW);
                DrawText("---f", 350, 500, 15, YELLOW);
            }

            if (isPaulse)
            {
                DrawText("HB", 400, 400, 48, YELLOW);
            }

            // + 1 and -1 for the umm chart to look right... idk why, but the first datapoint is zero alot?!
            // draw_chart_fit(50, 100, 800, 400, "Red Data               ", "", x, rd, DATA_PTS, RED);
            draw_chart_fit(50, 100, 800, 200, "IR Data", "", x, id, DATA_PTS, PURPLE);
            draw_chart(50, 300, 800, 200,
                       "CP DAT", "", 0, CP_COUNT, 0, 1000, x, cp, CP_COUNT, YELLOW);
        }

        if (activeScreen == 1)
        {
        }

        EndDrawing();
    }

    CloseWindow();
    hrr_close();
}