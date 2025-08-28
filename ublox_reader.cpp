#include <cstdint>
#include <iostream>
#include <cstring>

typedef struct
{
    uint32_t iTOW; // It tells us the variable is unsigned int and has 32 bits and it stores the Gps Time in milliseconds
    uint16_t year; //  It tells us the Year
    uint8_t month, day, hour, min, sec; //  It tells us the month,day,hr etc
    uint8_t fixType;  //  It will have a single byte dedicated to tell us in a way whether it is true or false but just instead of 0 and 1 it has 0,1,2 
    int32_t lon;     // It tells us the longitude
    int32_t lat;     //  It tells us the latitude
} UBXNavPVT; // Name of the struct

UBXNavPVT decodeUBXNavPVT(const uint8_t *buf) // decodeUBXNavPVT here would take the sequence of bytes it receives and convert into the above variables
{
    UBXNavPVT data;
    std::memcpy(&data.iTOW, buf + 0, sizeof(data.iTOW)); //It copies the first 4 bytes data from the buffer into the iTOW
    std::memcpy(&data.year, buf + 4, sizeof(data.year)); // It does the same as above just the starting position is index 4 of buffer
    // Rest does the same in order 
    data.month = buf[6];
    data.day = buf[7];
    data.hour = buf[8];
    data.min = buf[9];
    data.sec = buf[10];
    data.fixType = buf[11];
    std::memcpy(&data.lon, buf + 12, sizeof(data.lon));
    std::memcpy(&data.lat, buf + 16, sizeof(data.lat));
    return data;
}

double getLatitude(UBXNavPVT &d) { return d.lat / 1e7; } // It divides the latitude received from buffer by 10^7
double getLongitude(UBXNavPVT &d) { return d.lon / 1e7; }