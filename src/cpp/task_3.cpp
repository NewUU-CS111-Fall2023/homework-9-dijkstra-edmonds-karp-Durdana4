/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Problem3 {
public:
    int shortestPath(const vector<vector<char>>& maze) {
        int rows = maze.size();
        int cols = maze[0].size();
        
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        vector<vector<int>> distance(rows, vector<int>(cols, 0));
        
        int startX, startY, endX, endY;
        
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (maze[i][j] == 'S') {
                    startX = i;
                    startY = j;
                } else if (maze[i][j] == 'E') {
                    endX = i;
                    endY = j;
                }
            }
        }
        
        queue<pair<int, int>> q;
        q.push({startX, startY});
        visited[startX][startY] = true;
        
        while (!q.empty()) {
            int currX = q.front().first;
            int currY = q.front().second;
            q.pop();
            
            if (currX == endX && currY == endY) {
                return distance[currX][currY];
            }
            
            for (const auto& direction : directions) {
                int nextX = currX + direction[0];
                int nextY = currY + direction[1];
                
                if (nextX >= 0 && nextX < rows && nextY >= 0 && nextY < cols &&
                    maze[nextX][nextY] != '#' && !visited[nextX][nextY]) {
                    visited[nextX][nextY] = true;
                    distance[nextX][nextY] = distance[currX][currY] + 1;
                    q.push({nextX, nextY});
                }
            }
        }
        
        return -1;  // No valid path found
    }
};

int main() {
    Problem3 problem;
    
    vector<vector<char>> maze = {
        {'S', '.', '.', '#', '#'},
        {'#', '.', '#', '.', '#'},
        {'#', '.', '#', '.', '.'},
        {'#', '#', '#', '#', 'E'}
    };
    
    int shortestPathLength = problem.shortestPath(maze);
    
    if (shortestPathLength != -1) {
        cout << "Shortest path length: " << shortestPathLength << endl;
    } else {
        cout << "No valid path found." << endl;
    }
    
    return 0;
}
