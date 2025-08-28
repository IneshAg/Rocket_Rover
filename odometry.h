#ifndef ODOMETRY_H
#define ODOMETRY_H

#include <vector>
#include <utility>

struct Command
{
    double angle; // radians
    
    double time;  // seconds
};

class Odometry
{
public:
    // Convert path into motion commands
    std::vector<Command> computeCommands(const std::vector<std::pair<int, int>> &path,
                                         double grid_res, double speed);
};

#endif // ODOMETRY_H
