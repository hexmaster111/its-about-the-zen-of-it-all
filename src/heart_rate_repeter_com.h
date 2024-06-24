#ifndef HEART_RATE_REPETER_COM
#define HEART_RATE_REPETER_COM

enum MESSAGE_t
{

/*  - f  : float
 *  - d  : int
 *  - ld : long
 *  - NA : message header only
 *  # Messages*/
#define MESSAGE_MAX_HEADER_LEN 4
    /*
     *  | HEADER | DATA TYPE |            DESCRIPTION          |
     *  | ------ | --------- | ------------------------------- |*/
    /*  |   ND   |    NA     | There is no detected heart rate |*/
    MESSAGE_ND,
    /*  |   SP   |    f      | SPO2                            |*/
    MESSAGE_SP,
    /*  |   HR   |    d      | Heart Rate in BPM               |*/
    MESSAGE_HR,
    /*  |   CR   |    f      | Perstage Correlation  IR to RED |*/
    MESSAGE_CR,
    /*  |   TP   |    f      | Tempature of the sensor         |*/
    MESSAGE_TP,
    /*  |   RD   |    ld     | raw data of red led data        |*/
    MESSAGE_RD,
    /*  |   ID   |    ld     | raw data of  ir led data        |*/
    MESSAGE_ID,
    /*  |   RRMS |    f      | red rms value                   |*/
    MESSAGE_RRMS,
    /*  |   IRMS |    f      | ir rms value                    |*/
    MESSAGE_IRMS,

    __MESSAGE_COUNT
};

int hrr_open(const char *modem);
int hrr_close();

// 1 when got something
// 0 nothing
// xX  Read for data off of the port  Xx
int hrr_read(
    /*[out]*/ enum MESSAGE_t *msg,
    /*[out]*/ float *fv,
    /*[out]*/ int *iv,
    /*[out]*/ long *lv);

// 1 when got something
// 0 nothing
// xX  Retreave what the last msg was Xx
int hrr_get(
    /*[in]*/ enum MESSAGE_t *msg,
    /*[out]*/ float *fv,
    /*[out]*/ int *iv,
    /*[out]*/ long *lv,
    /*[out]*/ unsigned long *ticks);

#endif // HEART_RATE_REPETER_COM