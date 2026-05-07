// Write C++/Java program- There are flight paths between cities. If there is a flight between
// city A and city B then there is an edge between the cities. The cost of the edge can be the
// time that flight takes to reach city B from A or the amount of fuel used for the journey.
// Represent this as a graph. The node can be represented by airport name or name of the
// city. Use adjacency list representation of the graph or use adjacency matrix representation
// of the graph.
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

// Structure to represent a Flight (Edge)
struct Flight {
    string destination;
    int cost; // Can be time (mins) or fuel (liters)
};

class FlightGraph {
    int numCities;
    string cityNames[10];
    // Adjacency List: Each index has a list of 'Flight' objects
    list<Flight> adjList[10];

public:
    FlightGraph(int n) {
        numCities = n;
        // Let's assume some common cities for our flight network
        string names[] = {"Mumbai", "Pune", "Delhi", "Bangalore", "Chennai"};
        for (int i = 0; i < n; i++) {
            cityNames[i] = names[i];
        }
    }

    // Function to get city index by name
    int getIndex(string cityName) {
        for (int i = 0; i < numCities; i++) {
            if (cityNames[i] == cityName) return i;
        }
        return -1;
    }

    // Add a flight path
    void addFlight(string src, string dest, int cost) {
        int u = getIndex(src);
        int v = getIndex(dest);

        if (u != -1 && v != -1) {
            // Adding path from A to B (Directed)
            adjList[u].push_back({dest, cost});
            
            // If it's a round trip, add B to A as well
            // adjList[v].push_back({src, cost}); 
        }
    }

    // Display the adjacency list representation
    void display() {
        cout << "--- Flight Network (Adjacency List) ---" << endl;
        for (int i = 0; i < numCities; i++) {
            cout << cityNames[i] << " is connected to:" << endl;
            if (adjList[i].empty()) {
                cout << "  (No direct flights)" << endl;
            } else {
                for (auto flight : adjList[i]) {
                    cout << "  -> " << flight.destination << " [Cost/Time: " << flight.cost << "]" << endl;
                }
            }
            cout << endl;
        }
    }
};

int main() {
    int n = 5; // Mumbai, Pune, Delhi, Bangalore, Chennai
    FlightGraph spuFlights(n);

    // Adding some flight paths with costs (e.g., flight time in minutes)
    spuFlights.addFlight("Mumbai", "Delhi", 130);
    spuFlights.addFlight("Mumbai", "Bangalore", 95);
    spuFlights.addFlight("Pune", "Delhi", 125);
    spuFlights.addFlight("Delhi", "Chennai", 170);
    spuFlights.addFlight("Bangalore", "Chennai", 60);
    spuFlights.addFlight("Bangalore", "Mumbai", 100);

    spuFlights.display();

    return 0;
}