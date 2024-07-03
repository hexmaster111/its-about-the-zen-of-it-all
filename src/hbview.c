#include <raylib.h>
#include <stdio.h>
#include "heart_rate_repeter_com.h"
#include "chart.h"

int main(int argc, char *argv[])
{
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
}