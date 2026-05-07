// Implement a file compression algorithm that uses binary tree. Your program should Allow
// the user to compress and decompress messages containing alphabets using the standard
// Huffman algorithm for encoding and decoding.
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>

using namespace std;

// A Huffman tree node
struct Node {
    char data;
    int freq;
    Node *left, *right;

    Node(char d, int f) {
        data = d;
        freq = f;
        left = right = nullptr;
    }
};

// Comparison object to help the priority queue (Min-Heap)
struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

class Huffman {
private:
    map<char, string> huffmanCodes;
    Node* root;

    // Helper to traverse tree and store codes in a map
    void generateCodes(Node* root, string code) {
        if (!root) return;

        // If it's a leaf node, it contains a character
        if (root->data != '$') {
            huffmanCodes[root->data] = code;
        }

        generateCodes(root->left, code + "0");
        generateCodes(root->right, code + "1");
    }

public:
    Huffman() { root = nullptr; }

    void buildHuffmanTree(string text) {
        // 1. Count frequency of each character
        map<char, int> freq;
        for (char ch : text) freq[ch]++;

        // 2. Create a min-priority queue to store nodes
        priority_queue<Node*, vector<Node*>, compare> minHeap;

        for (auto const& [ch, f] : freq) {
            minHeap.push(new Node(ch, f));
        }

        // 3. Build the tree
        while (minHeap.size() != 1) {
            Node *left = minHeap.top(); minHeap.pop();
            Node *right = minHeap.top(); minHeap.pop();

            // Create internal node with '$' as placeholder and sum of frequencies
            Node *top = new Node('$', left->freq + right->freq);
            top->left = left;
            top->right = right;
            minHeap.push(top);
        }

        root = minHeap.top();
        generateCodes(root, "");
    }

    // Compression: Convert string to binary bits
    string compress(string text) {
        string encoded = "";
        for (char ch : text) {
            encoded += huffmanCodes[ch];
        }
        return encoded;
    }

    // Decompression: Convert binary bits back to string
    string decompress(string encoded) {
        string decoded = "";
        Node* curr = root;
        for (char bit : encoded) {
            if (bit == '0') curr = curr->left;
            else curr = curr->right;

            // If leaf node found
            if (curr->left == nullptr && curr->right == nullptr) {
                decoded += curr->data;
                curr = root;
            }
        }
        return decoded;
    }

    void displayCodes() {
        cout << "\n--- Huffman Codes ---" << endl;
        for (auto const& [ch, code] : huffmanCodes) {
            cout << ch << " : " << code << endl;
        }
    }
};

int main() {
    Huffman h;
    string text = "huffman algorithm example";

    cout << "Original Text: " << text << endl;

    h.buildHuffmanTree(text);
    h.displayCodes();

    string compressed = h.compress(text);
    cout << "\nCompressed (Binary): " << compressed << endl;

    string decompressed = h.decompress(compressed);
    cout << "Decompressed Text: " << decompressed << endl;

    return 0;
}