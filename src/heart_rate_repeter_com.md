# Messages

| HEADER | DATA TYPE | DESCRIPTION                     |
| ------ | --------- | ------------------------------- |
| ND     | NA        | There is no detected heart rate |
| SP     | f         | SPO2                            |
| HR     | d         | Heart Rate in BPM               |
| CR     | f         | Perstage Correlation  IR to RED |
| TP     | f         | Tempature of the sensor         |
| RD     | ld        | raw data of red led data        |
| ID     | ld        | raw data of  ir led data        |
| RRMS   | f         | red rms value                   |
| IRMS   | f         | ir rms value                    |
| Z      | f         |                                 |



# Message Data Types

| SYM | DESC                     |
| --- | ------------------------ |
| NA  | only header (for events) |
| f   | float                    |
| d   | int                      |
| ld  | long                     |

# Description

## Events

### ( ND ) No Data Event 

Sent whenever the Corrlation between ir and red is less then a threshold of calling this data "probbably good"



## Data

### ( IR )  IR Data 
### ( RD ) Red Data 

sent after reading the data out of the max30102's fifo buffer -- raw value right from sensor.


### ( IRMS ) Red Data Rms 
### ( IRMS )  Ir Data Rms 

over 128 samples