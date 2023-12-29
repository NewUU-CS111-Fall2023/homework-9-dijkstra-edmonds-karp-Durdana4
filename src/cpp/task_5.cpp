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

class Problem5 {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);
        
        for (const auto& flight : flights) {
            int from = flight[0];
            int to = flight[1];
            int price = flight[2];
            graph[from].push_back({to, price});
        }
        
        vector<vector<int>> dp(n, vector<int>(k + 2, numeric_limits<int>::max()));
        
        for (int i = 0; i <= k + 1; ++i) {
            dp[src][i] = 0;
        }
        
        queue<pair<int, int>> q;
        q.push({src, 0});
        
        while (!q.empty()) {
            int currCity = q.front().first;
            int currStops = q.front().second;
            q.pop();
            
            if (currStops > k + 1) {
                continue;
            }
            
            for (const auto& neighbor : graph[currCity]) {
                int nextCity = neighbor.first;
                int flightPrice = neighbor.second;
                
                if (dp[currCity][currStops] + flightPrice < dp[nextCity][currStops + 1]) {
                    dp[nextCity][currStops + 1] = dp[currCity][currStops] + flightPrice;
                    q.push({nextCity, currStops + 1});
                }
            }
        }
        
        int minPrice = numeric_limits<int>::max();
        for (int i = 1; i <= k + 1; ++i) {
            minPrice = min(minPrice, dp[dst][i]);
        }
        
        return (minPrice == numeric_limits<int>::max()) ? -1 : minPrice;
    }
};

int main() {
    Problem5 problem;
    
    int n = 3;
    vector<vector<int>> flights = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
    int src = 0;
    int dst = 2;
    int k = 1;
    
    int cheapestPrice = problem.findCheapestPrice(n, flights, src, dst, k);
    
    cout << "Cheapest price from source to destination with at most k stops: " << cheapestPrice << endl;
    
    return 0;
}
