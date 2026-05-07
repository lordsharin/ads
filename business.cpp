// Write C++/Java program -You have a business with several offices; you want to lease
// phone lines to connect them up with each other; and the phone company charges different
// amounts of money to connect different pairs of cities. You want a set of lines that connects
// all your offices with a minimum total cost. Solve the problem by suggesting appropriate
// data structures.
#include <iostream>
#include <vector>
#include <string>
#include <climits>

using namespace std;

#define V 5 // Number of offices
#define INF INT_MAX

class OfficeNetwork {
    string officeNames[V] = {"Mumbai", "Pune", "Bangalore", "Delhi", "Chennai"};
    int costMatrix[V][V];

public:
    OfficeNetwork() {
        // Initialize costs between offices (0 means same office, INF means no line)
        int initialCosts[V][V] = {
            {0, 200, 0, 600, 0},
            {200, 0, 300, 800, 500},
            {0, 300, 0, 0, 700},
            {600, 800, 0, 0, 900},
            {0, 500, 700, 900, 0}
        };

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (initialCosts[i][j] == 0 && i != j)
                    costMatrix[i][j] = INF;
                else
                    costMatrix[i][j] = initialCosts[i][j];
            }
        }
    }

    void findMinimumLease() {
        int parent[V];      // Array to store constructed MST
        int minWeight[V];   // Values used to pick minimum weight edge
        bool visited[V];    // To represent offices included in MST

        // Initialize all weights as infinite
        for (int i = 0; i < V; i++) {
            minWeight[i] = INF;
            visited[i] = false;
        }

        // Always include first office in MST
        minWeight[0] = 0;
        parent[0] = -1; // First node is always root of MST

        for (int count = 0; count < V - 1; count++) {
            // Pick the minimum weight office from the set of offices not yet visited
            int min = INF, u;

            for (int v = 0; v < V; v++) {
                if (!visited[v] && minWeight[v] < min) {
                    min = minWeight[v];
                    u = v;
                }
            }

            visited[u] = true;

            // Update minWeight and parent index of the adjacent offices
            for (int v = 0; v < V; v++) {
                if (costMatrix[u][v] && !visited[v] && costMatrix[u][v] < minWeight[v]) {
                    parent[v] = u;
                    minWeight[v] = costMatrix[u][v];
                }
            }
        }

        printMST(parent);
    }

    void printMST(int parent[]) {
        int totalCost = 0;
        cout << "Selected Phone Lines for Minimum Leasing Cost:\n";
        cout << "Connection \t\t Cost\n";
        for (int i = 1; i < V; i++) {
            cout << officeNames[parent[i]] << " <--> " << officeNames[i] << " \t " << costMatrix[i][parent[i]] << endl;
            totalCost += costMatrix[i][parent[i]];
        }
        cout << "\nTotal Minimum Cost to Connect All Offices: " << totalCost << endl;
    }
};

int main() {
    OfficeNetwork myBusiness;
    myBusiness.findMinimumLease();
    return 0;
}