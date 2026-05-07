// Beginning with an empty binary search tree, construct binary search tree by inserting the
// values in the order given. After constructing a binary tree -i. Insert new node, , ii. Find
// number of nodes in longest path from root, iii. Minimum data value found in the tree, iv.
// Change a tree so that the roles of the left and right pointers are swapped at every node, v.
// Search a value
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node *left, *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() { root = nullptr; }

    // i. Insert new node
    Node* insert(Node* root, int val) {
        if (root == nullptr) {
            return new Node(val);
        }
        if (val < root->data) {
            root->left = insert(root->left, val);
        } else {
            root->right = insert(root->right, val);
        }
        return root;
    }

    // ii. Find number of nodes in longest path (Height)
    int longestPath(Node* root) {
        if (root == nullptr) return 0;
        int leftHeight = longestPath(root->left);
        int rightHeight = longestPath(root->right);
        return max(leftHeight, rightHeight) + 1;
    }

    // iii. Minimum data value found in the tree
    int findMin(Node* root) {
        if (root == nullptr) return -1;
        Node* temp = root;
        while (temp->left != nullptr) {
            temp = temp->left; // Min is always in the leftmost leaf
        }
        return temp->data;
    }

    // iv. Swap left and right pointers (Mirror Image)
    void swapPointers(Node* root) {
        if (root == nullptr) return;

        // Swap the pointers
        Node* temp = root->left;
        root->left = root->right;
        root->right = temp;

        // Recursively swap for children
        swapPointers(root->left);
        swapPointers(root->right);
    }

    // v. Search a value
    bool search(Node* root, int val) {
        if (root == nullptr) return false;
        if (root->data == val) return true;

        if (val < root->data)
            return search(root->left, val);
        else
            return search(root->right, val);
    }

    // Helper: Inorder display to verify tree
    void display(Node* root) {
        if (root == nullptr) return;
        display(root->left);
        cout << root->data << " ";
        display(root->right);
    }
};

int main() {
    BST tree;
    int arr[] = {50, 30, 70, 20, 40, 60, 80};
    
    for (int x : arr) {
        tree.root = tree.insert(tree.root, x);
    }

    cout << "Inorder Traversal: ";
    tree.display(tree.root);
    
    cout << "\n\n1. Longest Path (Nodes): " << tree.longestPath(tree.root);
    cout << "\n2. Minimum Value: " << tree.findMin(tree.root);
    
    int key = 40;
    cout << "\n3. Search " << key << ": " << (tree.search(tree.root, key) ? "Found" : "Not Found");

    cout << "\n4. Swapping pointers (Mirroring tree)...";
    tree.swapPointers(tree.root);
    cout << "\nInorder after Swap: ";
    tree.display(tree.root); // Should be in descending order

    return 0;
}