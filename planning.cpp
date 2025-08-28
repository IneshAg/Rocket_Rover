#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>  
#include "planning.h"

struct Node
{
    int x, y;
    double cost;
    Node *parent;
};

std::vector<std::pair<int, int>> Planner::pathplanning(int startX, int startY, int goalX, int goalY, const std::vector<std::vector<int>> &grid)
{
    // Skeleton using BFS (replace with A* if needed)
    std::vector<std::pair<int, int>> path;

    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::queue<Node> q;
    q.push({startX, startY, 0, nullptr});
    visited[startX][startY] = true;

    Node *goalNode = nullptr;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!q.empty())
    {
        Node current = q.front();
        q.pop();
        if (current.x == goalX && current.y == goalY)
        {
            goalNode = new Node(current);
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 0 && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                q.push({nx, ny, 0, new Node(current)});
            }
        }
    }

    // reconstruct path
    Node *cur = goalNode;
    while (cur)
    {
        path.push_back({cur->x, cur->y});
        cur = cur->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}