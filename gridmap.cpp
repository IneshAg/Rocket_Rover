#include "gridmap.h"
#include <iostream>
#include <cmath> // for cos(), floor(), M_PI

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

Gridmapper::Gridmapper(GPS origin, double cellsize, int rows, int cols)
    : origin(origin), cellsize(cellsize), rows(rows), cols(cols),
      grid(rows, vector<bool>(cols, false))
{
    makemap();
    printgrid();
}

pair<int, int> Gridmapper::gpstogrid(const GPS &point) const
{
    double lat_m = (point.lat - origin.lat) * 111320.0;
    double lon_m = (point.lon - origin.lon) * (111320.0 * cos(deg2rad(origin.lat)));

    int row = static_cast<int>(floor(lat_m / cellsize));
    int col = static_cast<int>(floor(lon_m / cellsize));

    return {row, col};
}

vector<vector<bool>> Gridmapper::getGrid() const { return grid; }

double Gridmapper::deg2rad(double deg) const { return deg * M_PI / 180.0; }
bool Gridmapper::isvalid(int row, int col) const { return row >= 0 && row < rows && col >= 0 && col < cols; }

void Gridmapper::makemap()
{
    for (int r = 3; r < 8; r++)
        grid[r][2] = true;
    for (int c = 4; c < 9; c++)
        grid[6][c] = true;
}

void Gridmapper::printgrid() const
{
    cout << "The grid map is: " << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}
