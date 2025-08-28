#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "odometry.h"


std::vector<Command> Odometry::computeCommands(const std::vector<std::pair<int, int>> &path, double grid_res, double speed)
{
    std::vector<Command> commands;

    for (size_t i = 1; i < path.size(); i++)
    {
        int dx = path[i].first - path[i - 1].first;
        int dy = path[i].second - path[i - 1].second;
        double angle = atan2(dy, dx);
        double dist = sqrt(dx * dx + dy * dy) * grid_res;
        double t = dist / speed;

        commands.push_back({angle, t});
    }

    return commands;
}
