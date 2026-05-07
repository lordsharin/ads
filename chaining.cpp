// Implement all the functions of a dictionary (ADT) using hashing and handle collisions
// using chaining with / without replacement.Data: Set of (key, value) pairs, Keys are
// mapped to values, Keys must be comparable,Keys must be unique. Standard Operations:
// Insert(key, value), Find(key), Delete(key)
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Node {
    int key;
    string value;
    int chain; // Stores the index of the next element in the chain
};

class Dictionary {
    Node table[SIZE];

public:
    Dictionary() {
        for (int i = 0; i < SIZE; i++) {
            table[i].key = -1; // -1 indicates the slot is empty
            table[i].chain = -1;
        }
    }

    int hashFunction(int key) {
        return key % SIZE;
    }

    // --- Insert Without Replacement ---
    void insertWithoutReplacement(int key, string value) {
        int index = hashFunction(key);

        if (table[index].key == -1) {
            table[index].key = key;
            table[index].value = value;
        } else {
            // Collision occurred
            int current = index;
            // Find the end of the existing chain for this hash
            while (table[current].chain != -1) {
                current = table[current].chain;
            }

            // Find the next empty slot using linear probing
            int nextSlot = (index + 1) % SIZE;
            while (table[nextSlot].key != -1) {
                nextSlot = (nextSlot + 1) % SIZE;
                if (nextSlot == index) {
                    cout << "Table Full!" << endl;
                    return;
                }
            }

            // Place data and link the chain
            table[nextSlot].key = key;
            table[nextSlot].value = value;
            table[current].chain = nextSlot;
        }
    }

    // --- Find Operation ---
    void find(int key) {
        int index = hashFunction(key);
        int comparisons = 0;

        // If the key at home index doesn't match, we follow the chain
        int current = index;
        while (current != -1) {
            comparisons++;
            if (table[current].key == key) {
                cout << "Found: " << table[current].value << " (Comparisons: " << comparisons << ")" << endl;
                return;
            }
            current = table[current].chain;
        }
        cout << "Key " << key << " not found." << endl;
    }

    // --- Delete Operation (Simple Version) ---
    void remove(int key) {
        int index = hashFunction(key);
        int current = index;
        int prev = -1;

        while (current != -1 && table[current].key != key) {
            prev = current;
            current = table[current].chain;
        }

        if (current == -1) {
            cout << "Key not found for deletion." << endl;
            return;
        }

        // To keep it beginner-friendly, we reset the node. 
        // Note: Real-world deletion in chains is trickier!
        table[current].key = -1;
        table[current].value = "";
        
        // Update the previous node's chain to bypass the deleted node
        if (prev != -1) {
            table[prev].chain = table[current].chain;
        }
        table[current].chain = -1;
        
        cout << "Key " << key << " deleted." << endl;
    }

    void display() {
        cout << "\nIndex\tKey\tValue\tChain" << endl;
        for (int i = 0; i < SIZE; i++) {
            cout << i << "\t" << table[i].key << "\t" << table[i].value << "\t" << table[i].chain << endl;
        }
    }
};

int main() {
    Dictionary dict;
    
    dict.insertWithoutReplacement(12, "Apple");
    dict.insertWithoutReplacement(22, "Banana"); // Collision with 12
    dict.insertWithoutReplacement(42, "Cherry"); // Collision with 12
    dict.insertWithoutReplacement(15, "Date");
    
    dict.display();
    
    dict.find(22);
    dict.remove(22);
    dict.display();

    return 0;
}