#include "odometry.h"
#include <cmath>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

Odometry::Odometry(double wheel_radius, double rpm) : radius(wheel_radius), rpm(rpm)
{
    double rps = rpm / 60.0;              // revolutions per second
    linear_vel = 2 * M_PI * radius * rps; // linear velocity m/s
}

double Odometry::distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Odometry::angle(int x1, int y1, int x2, int y2)
{
    return atan2(y2 - y1, x2 - x1) * 180.0 / M_PI;
}

// Compute motion commands from path
MotionCommand Odometry::computeCommands(vector<pair<int, int>> &path)
{
    MotionCommand res = {0.0, 0.0};

    if (path.size() < 2)
        return res;

    for (size_t i = 1; i < path.size(); i++)
    {
        double dist = distance(path[i - 1].first, path[i - 1].second,
                               path[i].first, path[i].second);
        double ang = angle(path[i - 1].first, path[i - 1].second,
                           path[i].first, path[i].second);

        res.time_sec += dist / linear_vel; // time = distance/velocity
        res.angle_deg += ang;              // accumulate rotation angles
    }

    return res;
}
