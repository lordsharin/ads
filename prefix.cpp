//Construct an expression tree from the given prefix expression eg. +--a*b c/d e f and
//Traverse it using post order traversal (non recursive) and then delete the entire tree.
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Structure for a Tree Node
struct Node {
    char data;
    Node *left, *right;

    Node(char val) {
        data = val;
        left = right = nullptr;
    }
};

class ExpressionTree {
public:
    Node* root;

    ExpressionTree() { root = nullptr; }

    // Check if character is an operator
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    // Construct tree from Prefix Expression
    void constructFromPrefix(string prefix) {
        stack<Node*> st;

        // Traverse from right to left for Prefix
        for (int i = prefix.length() - 1; i >= 0; i--) {
            Node* newNode = new Node(prefix[i]);

            if (!isOperator(prefix[i])) {
                st.push(newNode);
            } else {
                // For prefix, the first pop is left, second is right
                newNode->left = st.top(); st.pop();
                newNode->right = st.top(); st.pop();
                st.push(newNode);
            }
        }
        root = st.top();
    }

    // Non-Recursive Post-order Traversal (using two stacks)
    void postOrderNonRecursive() {
        if (root == nullptr) return;

        stack<Node*> s1, s2;
        s1.push(root);

        while (!s1.empty()) {
            Node* curr = s1.top();
            s1.pop();
            s2.push(curr);

            if (curr->left) s1.push(curr->left);
            if (curr->right) s1.push(curr->right);
        }

        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
        cout << endl;
    }

    // Delete the entire tree
    void deleteTree(Node* node) {
        if (node == nullptr) return;

        // Delete subtrees first (Post-order deletion)
        deleteTree(node->left);
        deleteTree(node->right);

        cout << "Deleting node: " << node->data << endl;
        delete node;
    }
};

int main() {
    ExpressionTree et;
    
    // Example prefix: +--a*bc/def (Simplified version for clarity)
    // The prompt example: +--a*bc/def
    string prefix = "+--a*bc/def"; 

    cout << "Prefix Expression: " << prefix << endl;
    
    et.constructFromPrefix(prefix);

    cout << "Post-order Traversal (Non-recursive): ";
    et.postOrderNonRecursive();

    cout << "\nDeleting tree nodes..." << endl;
    et.deleteTree(et.root);
    et.root = nullptr;

    return 0;
}