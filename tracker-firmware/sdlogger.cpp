#include "sdlogger.h"
#include "config.h"
#include "gps.h"
#include "sensors_avr.h"

void datalog_setup()
{
    SD.begin(SPI_CS_PIN);
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    String header = "gps_time,gps_lat,gps_lon,gps_course,gps_speed_knots,gps_alt_meters,temp_in_f,temp_out_f";
    if(dataFile)
    {
        dataFile.println(header);
        dataFile.close();
    }
}

void log_data()
{
    //Log GPS info, internal and external temp
    char temp[16];
    String dataString;
    dataString += gps_time;
    dataString += ",";
    dataString += gps_aprs_lat;
    dataString += ",";
    dataString += gps_aprs_lon;
    dataString += ",";
    snprintf(temp, 4, "%03d", (int)gps_course);
    dataString += temp;
    dataString += ",";
    snprintf(temp, 4,  "%03d", (int)gps_speed);
    dataString += temp;
    dataString += ",";
    snprintf(temp, 7, "%06ld", (long)gps_altitude);
    dataString += temp;
    dataString += ",";
    snprintf(temp, 6, "%d", sensors_int_lm60());
    dataString += temp;
    dataString += ",";
    snprintf(temp, 6, "%d", sensors_ext_lm60());
    dataString += temp;
    
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    if(dataFile)
    {
        dataFile.println(dataString);
        dataFile.close();
    }
}
