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

class Problem2 {
public:
    vector<vector<int>> residualGraph;
    vector<vector<int>> flow;
    vector<int> parent;
    
    int bfs(int source, int sink) {
        fill(parent.begin(), parent.end(), -1);
        parent[source] = -2;
        
        queue<pair<int, int>> q;
        q.push({source, numeric_limits<int>::max()});
        
        while (!q.empty()) {
            int current = q.front().first;
            int flowSoFar = q.front().second;
            q.pop();
            
            for (int next = 0; next < residualGraph.size(); ++next) {
                if (parent[next] == -1 && residualGraph[current][next] > 0) {
                    parent[next] = current;
                    int updatedFlow = min(flowSoFar, residualGraph[current][next]);
                    
                    if (next == sink) {
                        return updatedFlow;
                    }
                    
                    q.push({next, updatedFlow});
                }
            }
        }
        
        return 0;
    }
    
    int edmondsKarp(const vector<vector<int>>& graph, int source, int sink) {
        int numVertices = graph.size();
        residualGraph = graph;
        flow.assign(numVertices, vector<int>(numVertices, 0));
        parent.resize(numVertices);
        
        int maxFlow = 0;
        int updatedFlow;
        
        while ((updatedFlow = bfs(source, sink)) > 0) {
            maxFlow += updatedFlow;
            
            int current = sink;
            while (current != source) {
                int prev = parent[current];
                flow[prev][current] += updatedFlow;
                flow[current][prev] -= updatedFlow;
                residualGraph[prev][current] -= updatedFlow;
                residualGraph[current][prev] += updatedFlow;
                current = prev;
            }
        }
        
        return maxFlow;
    }
};

int main() {
    Problem2 problem;
    
    vector<vector<int>> graph = {
        {0, 3, 0, 3, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 0},
        {3, 0, 0, 1, 2, 0, 0},
        {0, 0, 0, 0, 2, 6, 0},
        {0, 1, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 9},
        {0, 0, 0, 0, 0, 0, 0}
    };
    
    int sourceNode = 0;
    int sinkNode = 6;
    
    int maxFlow = problem.edmondsKarp(graph, sourceNode, sinkNode);
    
    cout << "Maximum flow from node " << sourceNode << " to node " << sinkNode << ": " << maxFlow << endl;
    
    return 0;
}
