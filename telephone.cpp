// Consider telephone book database of N clients. Make use of a hash table implementation
// to quickly look up client‘s telephone number. Make use of two collision handling
// techniques and compare them using number of comparisons required to find a set of
// telephone numbers
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Structure to store Client Data
struct Client {
    string name;
    string phone;
    bool isOccupied = false; // Used for Linear Probing
};

// Node for Separate Chaining
struct Node {
    string name;
    string phone;
    Node* next = nullptr;
};

const int TABLE_SIZE = 10;

class HashTable {
public:
    // 1. Linear Probing Implementation
    Client linearTable[TABLE_SIZE];

    // 2. Separate Chaining Implementation
    Node* chainingTable[TABLE_SIZE];

    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            chainingTable[i] = nullptr;
        }
    }

    // Simple Hash Function: Sum of ASCII values % Table Size
    int hashFunction(string key) {
        int sum = 0;
        for (char c : key) sum += c;
        return sum % TABLE_SIZE;
    }

    // Insert for Linear Probing
    void insertLinear(string name, string phone) {
        int index = hashFunction(name);
        while (linearTable[index].isOccupied) {
            index = (index + 1) % TABLE_SIZE; // Move to next slot
        }
        linearTable[index].name = name;
        linearTable[index].phone = phone;
        linearTable[index].isOccupied = true;
    }

    // Insert for Separate Chaining
    void insertChaining(string name, string phone) {
        int index = hashFunction(name);
        Node* newNode = new Node{name, phone, nullptr};
        if (chainingTable[index] == nullptr) {
            chainingTable[index] = newNode;
        } else {
            Node* temp = chainingTable[index];
            while (temp->next != nullptr) temp = temp->next;
            temp->next = newNode;
        }
    }

    // Search and count comparisons for Linear Probing
    int searchLinear(string name) {
        int index = hashFunction(name);
        int comparisons = 0;
        int startPos = index;

        do {
            comparisons++;
            if (linearTable[index].isOccupied && linearTable[index].name == name) {
                cout << "Linear Probing: Found " << name << " -> " << linearTable[index].phone << endl;
                return comparisons;
            }
            index = (index + 1) % TABLE_SIZE;
        } while (index != startPos && linearTable[index].isOccupied);

        cout << "Linear Probing: " << name << " not found." << endl;
        return comparisons;
    }

    // Search and count comparisons for Separate Chaining
    int searchChaining(string name) {
        int index = hashFunction(name);
        int comparisons = 0;
        Node* temp = chainingTable[index];

        while (temp != nullptr) {
            comparisons++;
            if (temp->name == name) {
                cout << "Chaining: Found " << name << " -> " << temp->phone << endl;
                return comparisons;
            }
            temp = temp->next;
        }

        cout << "Chaining: " << name << " not found." << endl;
        return comparisons;
    }
};

int main() {
    HashTable ht;
    
    // Sample Data
    string names[] = {"Alice", "Bob", "Charlie", "David", "Eve"};
    string phones[] = {"1234", "5678", "9101", "1121", "3141"};

    // Inserting data into both versions
    for (int i = 0; i < 5; i++) {
        ht.insertLinear(names[i], phones[i]);
        ht.insertChaining(names[i], phones[i]);
    }

    // Comparison Testing
    string searchTarget = "Eve";
    cout << "--- Search Comparison for: " << searchTarget << " ---" << endl;
    
    int compL = ht.searchLinear(searchTarget);
    int compC = ht.searchChaining(searchTarget);

    cout << "\n--- Performance Summary ---" << endl;
    cout << "Comparisons (Linear Probing): " << compL << endl;
    cout << "Comparisons (Separate Chaining): " << compC << endl;

    return 0;
}