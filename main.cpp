#include <iostream>
#include "ublox_reader.h"
#include "planning.h"
#include "odometry.h"

int main()
{
    // Sample raw GPS buffer (replace with actual UBX data)
    uint8_t buffer[20] = {/* fill with UBX payload */};
    UBXNavPVT gpsData = decodeUBXNavPVT(buffer);
    std::cout << "Lat: " << getLatitude(gpsData) << ", Lon: " << getLongitude(gpsData) << "\n";

    // Gridmap: 0 = free, 1 = obstacle
    std::vector<std::vector<int>> grid = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}};

    Planner planner;
    auto path = planner.pathplanning(0, 0, 2, 3, grid);

    Odometry odom;
    auto commands = odom.computeCommands(path, 1.0, 0.5);

    std::cout << "Commands:\n";
    for (auto &cmd : commands)
    {
        std::cout << "Angle: " << cmd.angle << ", Time: " << cmd.time << "\n";
    }

    return 0;
}
