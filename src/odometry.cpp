#include "../lib/odometry.h"
#include <cmath>
#include <vector>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

Odometry::Odometry(double wheel_radius, double rpm) : radius(wheel_radius), rpm(rpm)
{
    double rps = rpm / 60.0;              // revolutions per second
    linear_vel = 2 * M_PI * radius * rps; // linear velocity in m/s
}

double Odometry::distance(int x1, int y1, int x2, int y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Odometry::angle(int x1, int y1, int x2, int y2)
{
    // Convert atan2 (0°=east, CCW positive) into robot coords (0°=north, CW positive)
    double raw = atan2(y2 - y1, x2 - x1) * 180.0 / M_PI;
    double converted = fmod((450.0 - raw), 360.0);
    if (converted < 0)
        converted += 360.0;
    return converted;
}

// Compute motion commands from path
MotionCommand Odometry::computeCommands(std::vector<std::pair<int, int>> &path)
{
    MotionCommand res = {0.0, 0.0};
    if (path.size() < 2)
        return res;

    // --- CONFIG ---
    double cell_size = 1.0; // meters per grid cell (tune this; see below)
    // linear_vel already computed in ctor (m/s)

    // helpers
    auto grid_angle_deg = [&](int x1, int y1, int x2, int y2) -> double
    {
        // atan2 returns radians: 0 = +x (east), CCW positive
        double raw = atan2(double(y2 - y1), double(x2 - x1)) * 180.0 / M_PI;
        // convert to robot frame: 0 = north, clockwise positive
        double converted = fmod((450.0 - raw), 360.0);
        if (converted < 0)
            converted += 360.0;
        return converted;
    };

    // compute total grid distance (in grid units)
    double total_grid_dist = 0.0;
    for (size_t i = 1; i < path.size(); ++i)
    {
        double dx = double(path[i].first - path[i - 1].first);
        double dy = double(path[i].second - path[i - 1].second);
        total_grid_dist += sqrt(dx * dx + dy * dy);
    }

    // convert to meters
    double total_dist_m = total_grid_dist * cell_size;

    // time from physics
    res.time_sec = total_dist_m / linear_vel;

    // --- ANGLE accumulation ---
    // start orientation: assume robot initially faces NORTH (0 deg)
    double prev_angle = 0.0; // robot facing north at start
    double total_turn_deg = 0.0;

    for (size_t i = 1; i < path.size(); ++i)
    {
        double seg_angle = grid_angle_deg(path[i - 1].first, path[i - 1].second,
                                          path[i].first, path[i].second);
        double diff = seg_angle - prev_angle;
        // normalize to [-180,180]
        while (diff > 180.0)
            diff -= 360.0;
        while (diff < -180.0)
            diff += 360.0;
        total_turn_deg += fabs(diff);
        prev_angle = seg_angle;
    }

    res.angle_deg = total_turn_deg;
    return res;
}