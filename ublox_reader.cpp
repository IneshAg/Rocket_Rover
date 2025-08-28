#include <cstdint>
#include <iostream>
#include <cstring>

typedef struct
{
    uint32_t iTOW;
    uint16_t year;
    uint8_t month, day, hour, min, sec;
    uint8_t fixType;
    int32_t lon;
    int32_t lat;
} UBXNavPVT;

UBXNavPVT decodeUBXNavPVT(const uint8_t *buf)
{
    UBXNavPVT data;
    std::memcpy(&data.iTOW, buf + 0, sizeof(data.iTOW));
    std::memcpy(&data.year, buf + 4, sizeof(data.year));
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

double getLatitude(UBXNavPVT &d) { return d.lat / 1e7; }
double getLongitude(UBXNavPVT &d) { return d.lon / 1e7; }
