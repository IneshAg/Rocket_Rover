#include "../lib/ublox_reader.h"
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

static int NAV_POSLLH(uint8_t *buffer, classId *gps) {//This function takes the raw data from buffer and gives it to the struct GPS which has data we need in decoded form
  memcpy(&gps->iTOW, buffer, 4); // It take the first 4 bytes of buffer data and then stores it into the iTow[Time of week in ms ]
  memcpy(&gps->lon, buffer + 4, 4);//It take the first next  bytes of buffer data and then stores it into the iTow[Time of week in ms]
  // Rest follow the same pattern
  memcpy(&gps->lat, buffer + 8, 4);
  memcpy(&gps->height, buffer + 12, 4);
  memcpy(&gps->hMSL, buffer + 16, 4);
  memcpy(&gps->hAcc, buffer + 20, 4);
  memcpy(&gps->vAcc, buffer + 24, 4);
  return 0;
}

static vector<uint8_t> hexToBytes(const string &rawHex) { // It will convert the string of hex numbers to actual byte values
  vector<uint8_t> bytes;//Vector called bytes
  stringstream ss(rawHex);//Lets us read words from a string 
  string token;// Holds one hex number at a time 
  while (ss >> token) {
    bytes.push_back(static_cast<uint8_t>(stoul(token, nullptr, 16)));
  } // Converts the hex value to number[hexadecimal] and then adds it to the vector
  return bytes;
}

int decodeUBX(uint8_t *buffer, classId *gps) {
  
  if (buffer[0] == 0x01 && buffer[1] == 0x02) {
    return NAV_POSLLH(buffer + 4, gps); 
  }
  return 1;
}// First checks if the input it receives is of the right type and then only decodes it and also skips the first 4 bytes as the Gps data we need starts after it only 

GPS gpsFromData(const classId &gps) { // Convert the data we have which is raw right now into degrees and meters respectively
  GPS out;
  out.lat = gps.lat * 1e-7;
  out.lon = gps.lon * 1e-7;// Converts degree into a number 
  out.height = gps.height / 1000.0; // Convert mm to meters
  return out;
}

pair<GPS, GPS> readUbloxFile(const string &filename) {// It would open the file and checks whether the file can be opened and if not returns 2 Gps struct with zero values to avoid crash
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error: cannot open file " << filename << endl;
    return {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};
  }
  string rawStart, rawGoal;
  getline(file, rawStart);
  getline(file, rawGoal);

  cout << "Raw UBX Start: " << rawStart << endl;
  cout << "Raw UBX Goal : " << rawGoal << endl;
  // Using all the functions from above and would open the file and reads each line as a string and then convert the hex into numbers and bytes to useful data
  vector<uint8_t> startBytes = hexToBytes(rawStart);
  vector<uint8_t> goalBytes = hexToBytes(rawGoal);

  classId gpsStartData, gpsGoalData;
  decodeUBX(startBytes.data(), &gpsStartData);
  decodeUBX(goalBytes.data(), &gpsGoalData);

  GPS startGPS = gpsFromData(gpsStartData);
  GPS goalGPS = gpsFromData(gpsGoalData);

  file.close();

  return {startGPS, goalGPS};
}
