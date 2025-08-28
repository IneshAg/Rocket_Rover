#include "planning.h"
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

Planner::Planner(const vector<vector<bool>> &grid) : grid(grid)
{
    rows = grid.size();
    cols = grid[0].size();
}

bool Planner::isvalid(int x, int y) const
{
    return (x >= 0 && x < rows && y >= 0 && y < cols && !grid[x][y]);
}

double Planner::heuristic(int x1, int y1, int x2, int y2) const
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

// BFS path planning
vector<pair<int, int>> Planner::pathplanning(pair<int, int> start, pair<int, int> goal)
{
    vector<pair<int, int>> path;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
    queue<pair<int, int>> q;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    q.push(start);
    visited[start.first][start.second] = true;

    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        if (x == goal.first && y == goal.second)
            break;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (isvalid(nx, ny) && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                parent[nx][ny] = {x, y};
                q.push({nx, ny});
            }
        }
    }

    // reconstruct path
    pair<int, int> cur = goal;
    while (cur != make_pair(-1, -1))
    {
        path.push_back(cur);
        cur = parent[cur.first][cur.second];
    }
    reverse(path.begin(), path.end());
    return path;
}
