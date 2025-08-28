#ifndef ODOMETRY_H
#define ODOMETRY_H

#include <vector>
#include <utility>

// Motion command: total time and angle
struct MotionCommand
{
    double time_sec;
    double angle_deg;
};

class Odometry
{
private:
    double radius;     // wheel radius (meters)
    double rpm;        // wheel speed
    double linear_vel; // computed linear velocity

public:
    Odometry(double wheel_radius, double rpm);

    double distance(int x1, int y1, int x2, int y2);
    double angle(int x1, int y1, int x2, int y2);

    // Compute motion commands for given path
    MotionCommand computeCommands(std::vector<std::pair<int, int>> &path);
};

#endif // ODOMETRY_H
