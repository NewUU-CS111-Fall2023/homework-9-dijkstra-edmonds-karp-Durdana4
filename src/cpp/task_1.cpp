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

class Problem1 {
public:
    struct Edge {
        int destination;
        int weight;
        
        Edge(int dest, int w) : destination(dest), weight(w) {}
    };

    struct Node {
        int index;
        int distance;
        
        Node(int idx, int dist) : index(idx), distance(dist) {}
        
        bool operator>(const Node& other) const {
            return distance > other.distance;
        }
    };

    vector<int> dijkstra(const vector<vector<Edge>>& graph, int source) {
        int numNodes = graph.size();
        vector<int> distances(numNodes, numeric_limits<int>::max());
        vector<bool> visited(numNodes, false);
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        
        distances[source] = 0;
        pq.push(Node(source, 0));
        
        while (!pq.empty()) {
            Node currNode = pq.top();
            pq.pop();
            
            int currIndex = currNode.index;
            int currDist = currNode.distance;
            
            visited[currIndex] = true;
            
            for (const Edge& edge : graph[currIndex]) {
                int neighbor = edge.destination;
                int weight = edge.weight;
                
                if (!visited[neighbor] && currDist + weight < distances[neighbor]) {
                    distances[neighbor] = currDist + weight;
                    pq.push(Node(neighbor, distances[neighbor]));
                }
            }
        }
        
        return distances;
    }
};

int main() {
    Problem1 problem;
    
    vector<vector<Problem1::Edge>> graph = {
        {Problem1::Edge(1, 4), Problem1::Edge(2, 1)},
        {Problem1::Edge(3, 2)},
        {Problem1::Edge(1, 2), Problem1::Edge(3, 5)},
        {Problem1::Edge(4, 3)},
        {Problem1::Edge(0, 1), Problem1::Edge(3, 1)}
    };
    
    int sourceNode = 0;
    vector<int> distances = problem.dijkstra(graph, sourceNode);
    
    cout << "Shortest distances from node " << sourceNode << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        cout << "Node " << i << ": " << distances[i] << "\n";
    }
    
    return 0;
}
