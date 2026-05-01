#include <iostream>
#include <queue>
#include <vector>
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
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    void dfs(int startVertex) {
        vector<bool> visited(adjList.size(), false);
        vector<int> stack;

        stack.push_back(startVertex);

        while (!stack.empty()) {
            int currentVertex = stack.back();
            stack.pop_back();

            if (visited[currentVertex]) {
                continue;
            }

            visited[currentVertex] = true;
            cout << currentVertex << " ";

            for (const Pair &neighbor : adjList[currentVertex]) {
                if (!visited[neighbor.first]) {
                    stack.push_back(neighbor.first);
                }
            }
        }

        cout << endl;
    }

    void bfs(int startVertex) {
        vector<bool> visited(adjList.size(), false);
        queue<int> verticesToVisit;

        visited[startVertex] = true;
        verticesToVisit.push(startVertex);

        while (!verticesToVisit.empty()) {
            int currentVertex = verticesToVisit.front();
            verticesToVisit.pop();

            cout << currentVertex << " ";

            for (const Pair &neighbor : adjList[currentVertex]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    verticesToVisit.push(neighbor.first);
                }
            }
        }

        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,8}, {0,2,21}, {1,2,6}, {1,3,5}, {1,4,4}, {3,4,9},
        {2,7,11}, {2,8,8}, {5,6,10}, {5,7,15}, {5,8,5}, {6,7,3}, {6,8,7}
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    cout << "DFS starting from vertex 0:" << endl;
    graph.dfs(0);

    cout << "BFS starting from vertex 0:" << endl;
    graph.bfs(0);

    return 0;
}
