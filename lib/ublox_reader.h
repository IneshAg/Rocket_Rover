#ifndef UBLOX_READER_H
#define UBLOX_READER_H

#include <cstdint>
#include <string>
#include <utility>

// store GPS data which we need 
struct GPS {
  double lat;    // latitude
  double lon;    // longitude
  double height; // height in meters
};

// struct named  classId and it has all the data received from gps
struct classId {
  uint32_t iTOW;
  int32_t lon;    // in 1e-7 degrees
  int32_t lat;    // in 1e-7 degrees
  int32_t height; // height
  int32_t hMSL;   // height above sea level
  uint32_t hAcc;  // horizontal accuracy - long and lat accuracy
  uint32_t vAcc;  // vertical accuracy - height accuracy
};


int decodeUBX(uint8_t *buffer, classId *gps);

GPS gpsFromData(const classId &gps);

std::pair<GPS, GPS> readUbloxFile(const std::string &filename);

#endif // UBLOX_READER_H
