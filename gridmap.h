#ifndef GRIDMAP_H
#define GRIDMAP_H

#include <utility>
#include <vector>
#include <cmath>

struct GPS
{
    double lat;
    double lon;
};

class Gridmapper
{
    GPS origin;
    double cellsize;
    int rows, cols;
    std::vector<std::vector<bool>> grid;

public:
    Gridmapper(GPS origin, double cellsize, int rows, int cols);
    std::pair<int, int> gpstogrid(const GPS &gps) const;
    std::vector<std::vector<bool>> getGrid() const;

private:
    double deg2rad(double deg) const;
    bool isvalid(int row, int col) const;
    void makemap();
    void printgrid() const;
};

#endif // GRIDMAP_H
