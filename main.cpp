#include <iostream>
#include "ublox_reader.h"
#include "planning.h"
#include "odometry.h"

int main()
{
    // Simulate UBX GPS data
    uint8_t buf[20] = {0};
    *(uint32_t *)(buf + 0) = 123456;
    *(uint16_t *)(buf + 4) = 2025;
    buf[6] = 8;
    buf[7] = 28;
    buf[8] = 17;
    buf[9] = 0;
    buf[10] = 0;
    buf[11] = 3;
    *(int32_t *)(buf + 12) = 777777777;
    *(int32_t *)(buf + 16) = 123456789;

    // Decode GPS data
    UBXNavPVT start = decodeUBXNavPVT(buf);
    std::cout << "Lat: " << getLatitude(start)
              << ", Lon: " << getLongitude(start) << std::endl;

    // Create a simple 5x5 grid (0 = free, 1 = obstacle)
    std::vector<std::vector<int>> grid(5, std::vector<int>(5, 0));
    grid[2][2] = 1; // obstacle

    // Plan path
    Planner planner;
    std::vector<std::pair<int, int>> path = planner.pathplanning(0, 0, 4, 4, grid);

    // Generate odometry commands
    Odometry odo;
    double grid_res = 1.0; // 1 meter per cell
    double speed = 1.0;    // 1 m/s
    std::vector<Command> cmds = odo.computeCommands(path, grid_res, speed);

    // Print commands
    std::cout << "Commands:\n";
    for (auto &c : cmds)
    {
        std::cout << "Angle: " << c.angle << ", Time: " << c.time << std::endl;
    }
}
