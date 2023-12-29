/*
 * Author:
 * Date:
 * Name:
 */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>

using namespace std;

class Problem4 {
public:
    int networkDelayTime(const vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> graph(n + 1);
        
        for (const auto& time : times) {
            int source = time[0];
            int target = time[1];
            int weight = time[2];
            graph[source].push_back({target, weight});
        }
        
        vector<int> distance(n + 1, numeric_limits<int>::max());
        distance[k] = 0;
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, k});
        
        while (!pq.empty()) {
            int currNode = pq.top().second;
            int currDistance = pq.top().first;
            pq.pop();
            
            if (currDistance > distance[currNode]) {
                continue;
            }
            
            for (const auto& neighbor : graph[currNode]) {
                int nextNode = neighbor.first;
                int edgeWeight = neighbor.second;
                int totalDistance = currDistance + edgeWeight;
                
                if (totalDistance < distance[nextNode]) {
                    distance[nextNode] = totalDistance;
                    pq.push({totalDistance, nextNode});
                }
            }
        }
        
        int maxDelay = 0;
        for (int i = 1; i <= n; ++i) {
            if (distance[i] == numeric_limits<int>::max()) {
                return -1;
            }
            
            maxDelay = max(maxDelay, distance[i]);
        }
        
        return maxDelay;
    }
};

int main() {
    Problem4 problem;
    
    vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    int n = 4;
    int k = 2;
    
    int minTime = problem.networkDelayTime(times, n, k);
    
    cout << "Minimum time for all nodes to receive the signal: " << minTime << endl;
    
    return 0;
}
