#ifndef UBLOX_READER_H
#define UBLOX_READER_H

#include <cstdint>
#include <string>
#include <utility>

// Struct to hold GPS info after decoding
struct GPSData
{
    double lat;
    double lon;
    double height;
};

// Struct representing UBX binary data (raw values)
struct classId
{
    uint32_t iTOW;
    int32_t lon;
    int32_t lat;
    int32_t height;
    int32_t hMSL;
    int32_t hAcc;
    int32_t vAcc;
};

// Decode UBX NAV-POSLLH from buffer
int decodeUBX(uint8_t *buffer, classId *gps);

// Convert decoded UBX data to readable GPS
GPSData gpsFromData(const classId &gps);

// Read GPS start/goal from a UBX hex file
std::pair<GPSData, GPSData> readUbloxFile(const std::string &filename);

#endif // UBLOX_READER_H
