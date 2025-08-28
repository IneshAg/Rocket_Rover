#ifndef PLANNING_H
#define PLANNING_H

#include <vector>
#include <utility>

class Planner
{
public:
    // Grid-based path planning from start to goal
    std::vector<std::pair<int, int>> pathplanning(
        int startX, int startY,
        int goalX, int goalY,
        const std::vector<std::vector<int>> &grid);
};

#endif // PLANNING_H
