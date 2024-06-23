#ifndef HEART_RATE_REPETER_COM
#define HEART_RATE_REPETER_COM

enum MESSAGE_t
{

    /*  - f  : float
     *  - d  : int
     *  - ld : long
     *  - NA : message header only
     *  # Messages
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
    /*  |   Z    |    f      |                                 |*/
    MESSAGE_Z,
};

int hrr_open(const char *modem);

#endif // HEART_RATE_REPETER_COM