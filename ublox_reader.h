#ifndef UBLOX_READER_H
#define UBLOX_READER_H

#include <cstdint>

// Struct for UBX NAV-PVT message
typedef struct
{
    uint32_t iTOW; // GPS time of week [ms]
    uint16_t year;
    uint8_t month, day, hour, min, sec;
    uint8_t fixType;
    int32_t lon; // degrees * 1e7
    int32_t lat; // degrees * 1e7
} UBXNavPVT;

// Function to decode NAV-PVT from raw buffer
UBXNavPVT decodeUBXNavPVT(const uint8_t *buf);

// Convert to degrees
double getLatitude(UBXNavPVT &d);
double getLongitude(UBXNavPVT &d);

#endif // UBLOX_READER_H
