#include "planning.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>

struct Node
{
    int x, y;
    Node *parent;
};

std::vector<std::pair<int, int>> Planner::pathplanning(
    int startX, int startY,
    int goalX, int goalY,
    const std::vector<std::vector<int>> &grid)
{
    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::queue<Node *> q;

    Node *startNode = new Node{startX, startY, nullptr};
    q.push(startNode);
    visited[startX][startY] = true;

    Node *goalNode = nullptr;

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();
        if (current->x == goalX && current->y == goalY)
        {
            goalNode = current;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = current->x + dx[i];
            int ny = current->y + dy[i];
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && grid[nx][ny] == 0 && !visited[nx][ny])
            {
                visited[nx][ny] = true;
                Node *next = new Node{nx, ny, current};
                q.push(next);
            }
        }
    }

    std::vector<std::pair<int, int>> path;
    Node *cur = goalNode;
    while (cur)
    {
        path.push_back({cur->x, cur->y});
        cur = cur->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}
