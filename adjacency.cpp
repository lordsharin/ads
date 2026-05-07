// Write C++/Java program to Represent a given graph using adjacency matrix/list to
// perform DFS and using adjacency list to perform BFS. Use the map of the area around the
// college as the graph. Identify the prominent land marks as nodes and perform DFS and
// BFS on that.
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <string>

using namespace std;

class CampusMap {
    int V; // Number of landmarks
    vector<string> landmarkNames;
    int adjMatrix[10][10];       // Adjacency Matrix
    vector<list<int>> adjList;   // Adjacency List

public:
    CampusMap(int vertices) {
        V = vertices;
        adjList.resize(V);
        landmarkNames = {"Main Gate", "Chaturshringi", "Pashan Circle", "Aundh IT Park", "E-Square"};

        // Initialize Matrix with 0
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                adjMatrix[i][j] = 0;
    }

    // Add road connectivity (Edge)
    void addRoad(int u, int v) {
        // For Adjacency Matrix
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // For Adjacency List
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // BFS using Adjacency List
    void BFS(int startNode) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[startNode] = true;
        q.push(startNode);

        cout << "BFS Traversal: ";
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            cout << landmarkNames[curr] << " -> ";

            for (int neighbor : adjList[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << "End" << endl;
    }

    // DFS using Adjacency Matrix (Recursive)
    void DFS(int startNode, vector<bool>& visited) {
        visited[startNode] = true;
        cout << landmarkNames[startNode] << " -> ";

        for (int i = 0; i < V; i++) {
            if (adjMatrix[startNode][i] == 1 && !visited[i]) {
                DFS(i, visited);
            }
        }
    }
};

int main() {
    CampusMap myArea(5);

    // Creating the map connectivity
    myArea.addRoad(0, 1); // Main Gate to Chaturshringi
    myArea.addRoad(0, 4); // Main Gate to E-Square
    myArea.addRoad(1, 2); // Chaturshringi to Pashan Circle
    myArea.addRoad(2, 3); // Pashan Circle to Aundh IT Park
    myArea.addRoad(3, 0); // Aundh IT Park to Main Gate

    cout << "--- Landmark Exploration around College ---" << endl;
    
    // Perform BFS
    myArea.BFS(0);

    // Perform DFS
    vector<bool> visited(5, false);
    cout << "DFS Traversal: ";
    myArea.DFS(0, visited);
    cout << "End" << endl;

    return 0;
}