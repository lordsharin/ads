// SA Dictionary stores keywords and its meanings. Provide facility for adding new keywords,
// deleting keywords, updating values of any entry. Provide facility to display whole data
// sorted in ascending/ Descending order. Also find how many maximum comparisons may
// require for finding any keyword. Use Height balance tree and find the complexity for
// finding a keyword
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    string keyword;
    string meaning;
    Node *left, *right;
    int height;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

class Dictionary {
public:
    Node* root = nullptr;

    int getHeight(Node* n) { return n ? n->height : 0; }

    int getBalance(Node* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    Node* insert(Node* node, string key, string mean) {
        if (!node) return new Node(key, mean);

        if (key < node->keyword)
            node->left = insert(node->left, key, mean);
        else if (key > node->keyword)
            node->right = insert(node->right, key, mean);
        else return node; // Duplicate keys not allowed

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        // Balancing Logic (LL, RR, LR, RL cases)
        if (balance > 1 && key < node->left->keyword) return rightRotate(node);
        if (balance < -1 && key > node->right->keyword) return leftRotate(node);
        if (balance > 1 && key > node->left->keyword) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->keyword) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void update(Node* node, string key, string newMean) {
        if (!node) { cout << "Not found!\n"; return; }
        if (key == node->keyword) node->meaning = newMean;
        else if (key < node->keyword) update(node->left, key, newMean);
        else update(node->right, key, newMean);
    }

    void displayAscending(Node* node) {
        if (!node) return;
        displayAscending(node->left);
        cout << node->keyword << " : " << node->meaning << endl;
        displayAscending(node->right);
    }

    void displayDescending(Node* node) {
        if (!node) return;
        displayDescending(node->right);
        cout << node->keyword << " : " << node->meaning << endl;
        displayDescending(node->left);
    }
};

int main() {
    Dictionary dict;
    dict.root = dict.insert(dict.root, "Apple", "A red fruit");
    dict.root = dict.insert(dict.root, "Banana", "A yellow fruit");
    dict.root = dict.insert(dict.root, "Zebra", "A striped animal");

    cout << "Ascending Order:\n";
    dict.displayAscending(dict.root);

    dict.update(dict.root, "Apple", "A fruit that keeps the doctor away");
    cout << "\nAfter Update (Descending):\n";
    dict.displayDescending(dict.root);

    return 0;
}