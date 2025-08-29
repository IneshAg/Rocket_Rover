#include "../lib/planning.h"
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

Planner::Planner(const vector<vector<bool>> &grid) : grid(grid) {
  rows = grid.size();
  cols = grid[0].size();
}
// It takes a grid as input and stores and then calculates the number of rows and columns

bool Planner::isvalid(int x, int y) const {
  return (x >= 0 && x < rows && y >= 0 && y < cols && !grid[x][y]);
}
// it checks whether X and Y are inside the grid or not and if the Coordinates are an obstacle or not

double Planner::heuristic(int x1, int y1, int x2, int y2) const {
  return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

vector<pair<int, int>> Planner::pathplanning(pair<int, int> start,
                                             pair<int, int> goal) {
  vector<pair<int, int>> path; // store final path 
  
  // If start or goal is invalid, return empty path
  if (!isvalid(start.first, start.second) || !isvalid(goal.first, goal.second)) {
    return path;
  }
  
  // If start equals goal, return path with just the start point
  if (start == goal) {
    path.push_back(start);
    return path;
  }
  
  // BFS implementation
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));
  vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));
  queue<pair<int, int>> q;
  
  // 4-directional movement: up, down, left, right
  int dx[4] = {-1, 1, 0, 0};
  int dy[4] = {0, 0, -1, 1};
  
  // BFS checks all the layers one by one and marks them as visited to avoid checking it again and again and also at the same time marks the required path
  q.push(start);
  visited[start.first][start.second] = true;
  
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    
    // If we reached the goal, break
    if (x == goal.first && y == goal.second) {
      break;
    }
    
    // Check all 4 directions
    for (int i = 0; i < 4; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      
      if (isvalid(nx, ny) && !visited[nx][ny]) {
        visited[nx][ny] = true;
        parent[nx][ny] = {x, y};
        q.push({nx, ny});
      }
    }
  }
  
  // Check if path was actually found (goal is reachable)
  if (parent[goal.first][goal.second] == make_pair(-1, -1)) {
    return {}; // no path found
  }
  
  // Reconstruct path from goal back to start
  pair<int, int> current = goal;
  while (current != make_pair(-1, -1)) {
    path.push_back(current);
    current = parent[current.first][current.second];
  }
  
  // Reverse to get path from start to goal
  reverse(path.begin(), path.end());
  
  return path;
}
