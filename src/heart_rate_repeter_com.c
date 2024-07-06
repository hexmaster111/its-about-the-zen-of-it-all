#include "heart_rate_repeter_com.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#ifndef __USE_MISC // really this is for my intellasence...
#define __USE_MISC
#endif

#include <termios.h>
int hr_port;

struct
{
    float f;
    int i;
    long l;
    clock_t last_got;
} msg_history[__MESSAGE_COUNT] = {0};

void hrr_init()
{
    hr_port = -1;
}

int read_int(const char *read_buff, size_t split_p, int read_buff_n)
{

    char number_letters[16] = {0};

    const char *text = read_buff + split_p;

    for (size_t i = 0; i < read_buff_n - split_p; i++)
    {

        if (text[i] == '\n' || text[i] == '\r')
        {
            // we have all the number
            number_letters[i + 1] = '\0';
            return atoi(number_letters);
        }

        number_letters[i] = text[i];
    }

    return 0;
}

long read_long(const char *read_buff, size_t split_p, int read_buff_n)
{

    char number_letters[16] = {0};

    const char *text = read_buff + split_p;

    for (size_t i = 0; i < read_buff_n - split_p; i++)
    {

        if (text[i] == '\n' || text[i] == '\r')
        {
            // we have all the number
            number_letters[i + 1] = '\0';
            return atol(number_letters);
        }

        number_letters[i] = text[i];
    }

    return 0;
}

float read_float(const char *read_buff, size_t split_p, int read_buff_n)
{

    char number_letters[16] = {0};

    const char *text = read_buff + split_p;

    for (size_t i = 0; i < read_buff_n - split_p; i++)
    {

        if (text[i] == '\n' || text[i] == '\r')
        {
            // we have all the number
            number_letters[i + 1] = '\0';
            return atof(number_letters);
        }

        number_letters[i] = text[i];
    }

    return 0;
}

// 1 when got something
// 0 nothing
int hrr_read(enum MESSAGE_t *msg, float *fv, int *iv, long *lv)
{
    char read_buf[256];
    int n = read(hr_port, &read_buf, sizeof(read_buf));

    if (0 >= n)
    {
        return 0;
    }

    char msg_header[MESSAGE_MAX_HEADER_LEN] = {0};

    size_t msg_len;

    for (msg_len = 0; msg_len < n; msg_len++)
    {
        if (read_buf[msg_len] == ' ' ||
            read_buf[msg_len] == '\n' ||
            read_buf[msg_len] == '\r')
        {
            // found all the header chars
            msg_header[msg_len + 1] = '\0';
            break;
        }

        msg_header[msg_len] = read_buf[msg_len];
    }

    // fprintf(stdout, "%s", read_buf);

    if (strcmp(msg_header, "ND") == 0)
    {
        *msg = MESSAGE_ND;
        msg_history[(int)*msg].last_got = clock();
        return 1;
    }
    else if (strcmp(msg_header, "SP") == 0)
    {
        *msg = MESSAGE_SP;
        msg_history[(int)*msg].last_got = clock();
        *fv = msg_history[(int)*msg].f = read_float(read_buf, msg_len, n);
        return 1;
    }
    else if (strcmp(msg_header, "ID") == 0)
    {
        *msg = MESSAGE_ID;
        msg_history[(int)*msg].last_got = clock();
        *lv = msg_history[(int)*msg].l = read_long(read_buf, msg_len, n);
        return 1;
    }
    else if (strcmp(msg_header, "RD") == 0)
    {
        *msg = MESSAGE_RD;
        msg_history[(int)*msg].last_got = clock();
        *lv = msg_history[(int)*msg].l = read_long(read_buf, msg_len, n);
        return 1;
    }
    else if (strcmp(msg_header, "HR") == 0)
    {
        *msg = MESSAGE_HR;
        msg_history[(int)*msg].last_got = clock();
        *iv = msg_history[(int)*msg].i = read_int(read_buf, msg_len, n);
        return 1;
    }
    else if (strcmp(msg_header, "TP") == 0)
    {
        *msg = MESSAGE_TP;
        msg_history[(int)*msg].last_got = clock();
        *fv = msg_history[(int)*msg].f = read_float(read_buf, msg_len, n);
        return 1;
    }
    else if (strcmp(msg_header, "CR") == 0)
    {
        *msg = MESSAGE_CR;
        msg_history[(int)*msg].last_got = clock();
        *fv = msg_history[(int)*msg].f = read_float(read_buf, msg_len, n);
        return 1;
    }
    else if (strcmp(msg_header, "RRMS") == 0)
    {
        *msg = MESSAGE_CR;
        msg_history[(int)*msg].last_got = clock();
        *fv = msg_history[(int)*msg].f = read_float(read_buf, msg_len, n);
        return 1;
    }
    else if (strcmp(msg_header, "IRMS") == 0)
    {
        *msg = MESSAGE_CR;
        msg_history[(int)*msg].last_got = clock();
        *fv = msg_history[(int)*msg].f = read_float(read_buf, msg_len, n);
        return 1;
    }
    else
    {
        fprintf(stdout, "unhandled msg : \'%s\'\n", msg_header);
        return 0;
    }

    return 0;
}

int hrr_is_open()
{
    return hr_port > 0;
}

int hrr_close()
{
    return close(hr_port);
}

int hrr_open(const char *modem)
{
    hr_port = open(modem, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (hr_port < 0)
    {
        fprintf(stderr, "Could not open port!");
        return 0;
    }

    struct termios tty = {0};
    tty.c_cflag &= ~PARENB;                                                      // no parity
    tty.c_cflag &= ~CSTOPB;                                                      // no stop bit
    tty.c_cflag |= CS8;                                                          // 8 bits per byte
    tty.c_cflag &= ~CRTSCTS;                                                     // Disable RTS/CTS hardware flow control
    tty.c_cflag |= CREAD | CLOCAL;                                               // read, and no ctrl lines
    tty.c_lflag |= ICANON;                                                       // \n bufferd mode
    tty.c_lflag &= ~ECHO;                                                        // Disable echo
    tty.c_lflag &= ~ECHOE;                                                       // Disable erasure
    tty.c_lflag &= ~ECHONL;                                                      // Disable new-line echo
    tty.c_lflag &= ~ISIG;                                                        // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);                                      // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL); // Disable any special handling of received bytes
    tty.c_oflag &= ~OPOST;                                                       // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR;                                                       // Prevent conversion of newline to carriage return/line feed
    tty.c_cc[VTIME] = 0;                                                         // not sure that i need to set these with noblock opening it
    tty.c_cc[VMIN] = 0;

    cfsetspeed(&tty, B9600);

    if (tcsetattr(hr_port, TCSANOW, &tty) != 0)
    {
        fprintf(stderr, "Error saving port settings!\n");
        return 0;
    }

    return 1;
}
