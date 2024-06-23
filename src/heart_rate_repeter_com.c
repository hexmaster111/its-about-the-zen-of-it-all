#include "heart_rate_repeter_com.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef __USE_MISC // really this is for my intellasence...
#define __USE_MISC
#endif

#include <termios.h>

int hrr_open(const char *modem)
{
    int port = open(modem, O_RDWR | O_NOCTTY);
    if (port < 0)
    {
        fprintf(stderr, "Could not open port!");
        return 0;
    }

    struct termios tty = {0};
    tty.c_cflag &= ~PARENB;  // no parity
    tty.c_cflag &= ~CSTOPB;  // no stop bit
    tty.c_cflag |= CS8;      // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control

    return 1;
}
