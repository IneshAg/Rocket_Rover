#ifndef PLANNING_H
#define PLANNING_H

#include <vector>
#include <utility> // for std::pair

class Planner
{
public:
    // Compute path from start to goal over grid
    // grid: 0 = free, 1 = obstacle
    std::vector<std::pair<int, int>> pathplanning(int startX, int startY, int goalX, int goalY,
                                                  const std::vector<std::vector<int>> &grid);
};

#endif // PLANNING_H
