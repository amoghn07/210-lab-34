#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <limits>
using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph(const vector<string> &labels) {
        cout << "Campus Shuttle Network Topology:" << endl;
        cout << "================================" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << "Stop " << i << " (" << labels[i] << ") connects to:" << endl;
            for (Pair v : adjList[i]) {
                cout << "  -> Stop " << v.first << " (" << labels[v.first] << ", "
                     << v.second << " minutes)" << endl;
            }
            cout << endl;
        }
    }

    void dfs(int startVertex, const vector<string> &labels) {
        vector<bool> visited(adjList.size(), false);
        vector<int> stack;

        stack.push_back(startVertex);

        cout << "Campus Shuttle Trace (DFS) from Stop " << startVertex << " (" << labels[startVertex]
             << "):" << endl;
        cout << "Purpose: Tracing one possible route across campus" << endl;
        cout << "=======================================" << endl;

        while (!stack.empty()) {
            int currentVertex = stack.back();
            stack.pop_back();

            if (visited[currentVertex]) {
                continue;
            }

            visited[currentVertex] = true;
            cout << "Inspecting Stop " << currentVertex << " (" << labels[currentVertex] << ")" << endl;

            for (const Pair &neighbor : adjList[currentVertex]) {
                if (!visited[neighbor.first]) {
                    cout << "  -> Potential route to Stop " << neighbor.first << " (" << labels[neighbor.first]
                         << ") - " << neighbor.second << " minutes" << endl;
                    stack.push_back(neighbor.first);
                }
            }
        }
    }

    void bfs(int startVertex, const vector<string> &labels) {
        vector<bool> visited(adjList.size(), false);
        queue<int> verticesToVisit;

        visited[startVertex] = true;
        verticesToVisit.push(startVertex);

        cout << "" << endl;
        cout << "Campus Shuttle Coverage (BFS) from Stop " << startVertex << " (" << labels[startVertex]
             << "):" << endl;
        cout << "Purpose: Analyzing nearby stops by travel layer" << endl;
        cout << "==============================================" << endl;

        while (!verticesToVisit.empty()) {
            int currentVertex = verticesToVisit.front();
            verticesToVisit.pop();

            cout << "Checking Stop " << currentVertex << " (" << labels[currentVertex] << ")" << endl;

            for (const Pair &neighbor : adjList[currentVertex]) {
                if (!visited[neighbor.first]) {
                    cout << "  -> Next service area: Stop " << neighbor.first << " (" << labels[neighbor.first]
                         << ") - " << neighbor.second << " minutes" << endl;
                    visited[neighbor.first] = true;
                    verticesToVisit.push(neighbor.first);
                }
            }
        }
    }

    vector<int> shortestPaths(int startVertex) {
        vector<int> distances(adjList.size(), numeric_limits<int>::max());
        priority_queue<Pair, vector<Pair>, greater<Pair>> minHeap;

        distances[startVertex] = 0;
        minHeap.push(make_pair(0, startVertex));

        while (!minHeap.empty()) {
            int currentDistance = minHeap.top().first;
            int currentVertex = minHeap.top().second;
            minHeap.pop();

            if (currentDistance > distances[currentVertex]) {
                continue;
            }

            for (const Pair &neighbor : adjList[currentVertex]) {
                int nextVertex = neighbor.first;
                int edgeWeight = neighbor.second;

                if (distances[currentVertex] != numeric_limits<int>::max() &&
                    distances[currentVertex] + edgeWeight < distances[nextVertex]) {
                    distances[nextVertex] = distances[currentVertex] + edgeWeight;
                    minHeap.push(make_pair(distances[nextVertex], nextVertex));
                }
            }
        }

        return distances;
    }
};

int main() {
    vector<string> stopNames = {
        "Campus Transit Center",
        "Student Union",
        "Library",
        "Engineering Hall",
        "Science Center",
        "Residence Hall",
        "Recreation Center",
        "Parking Garage",
        "Administration Building"
    };

    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,8}, {0,2,21}, {1,2,6}, {1,3,5}, {1,4,4}, {3,4,9},
        {2,7,11}, {2,8,8}, {5,6,10}, {5,7,15}, {5,8,5}, {6,7,3}, {6,8,7}
    };

    // Creates graph
    Graph graph(edges);

    // Prints the campus shuttle network representation
    graph.printGraph(stopNames);

    graph.dfs(0, stopNames);
    graph.bfs(0, stopNames);

    vector<int> distances = graph.shortestPaths(0);
    cout << endl;
    cout << "Shortest path from node 0:" << endl;
    for (int i = 0; i < distances.size(); i++) {
        cout << 0 << " -> " << i << " : " << distances[i] << endl;
    }

    return 0;
}
