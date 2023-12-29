/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Problem6 {
public:
    int findShortestPath(int n, vector<vector<int>>& flights, int src, int dst, int k, int f) {
        vector<vector<pair<int, pair<int, int>>>> graph(n);
        
        for (const auto& flight : flights) {
            int from = flight[0];
            int to = flight[1];
            int distance = flight[2];
            int availability = flight[3];
            graph[from].push_back({to, {distance, availability}});
        }
        
        vector<vector<int>> dp(n, vector<int>(k + 1, numeric_limits<int>::max()));
        
        for (int i = 0; i <= k; ++i) {
            dp[src][i] = 0;
        }
        
        queue<pair<int, pair<int, int>>> q;
        q.push({src, {0, f}});
        
        while (!q.empty()) {
            int currCity = q.front().first;
            int currDistance = q.front().second.first;
            int currFuel = q.front().second.second;
            q.pop();
            
            if (currDistance > dp[currCity][currFuel]) {
                continue;
            }
            
            for (const auto& neighbor : graph[currCity]) {
                int nextCity = neighbor.first;
                int flightDistance = neighbor.second.first;
                int availability = neighbor.second.second;
                
                if (flightDistance <= currFuel && currDistance + flightDistance < dp[nextCity][currFuel - flightDistance]) {
                    dp[nextCity][currFuel - flightDistance] = currDistance + flightDistance;
                    q.push({nextCity, {dp[nextCity][currFuel - flightDistance], currFuel - flightDistance}});
                }
                
                if (availability == 1 && currDistance < dp[nextCity][f]) {
                    dp[nextCity][f] = currDistance;
                    q.push({nextCity, {dp[nextCity][f], f}});
                }
            }
        }
        
        int shortestPath = numeric_limits<int>::max();
        for (int i = 0; i <= k; ++i) {
            shortestPath = min(shortestPath, dp[dst][i]);
        }
        
        return (shortestPath == numeric_limits<int>::max()) ? -1 : shortestPath;
    }
};

int main() {
    Problem6 problem;
    
    int n = 4;
    vector<vector<int>> flights = {{0, 1, 100, 0}, {0, 2, 500, 1}, {1, 2, 100, 0}, {2, 3, 200, 1}};
    int src = 0;
    int dst = 3;
    int k = 1;
    int f = 200;
    
    int shortestPath = problem.findShortestPath(n, flights, src, dst, k, f);
    
    cout << "Shortest possible path from source to destination with at most k stops and fuel capacity f: " << shortestPath << endl;
    
    return 0;
}
