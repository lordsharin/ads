// A book consists of chapters, chapters consist of sections and sections consist of subsections.
// Construct a tree and print the nodes. Find the time and space requirements of your method
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure for a tree node
struct Node {
    string label;
    vector<Node*> children;

    Node(string name) {
        label = name;
    }
};

class BookTree {
public:
    Node* root;

    BookTree() {
        root = nullptr;
    }

    // Function to create the book structure
    void createBook() {
        root = new Node("Book: Computer Graphics");

        // Adding Chapters
        root->children.push_back(new Node("Chapter 1: Introduction"));
        root->children.push_back(new Node("Chapter 2: Scan Conversion"));

        // Adding Sections to Chapter 1
        root->children[0]->children.push_back(new Node("Section 1.1: Applications"));
        root->children[0]->children.push_back(new Node("Section 1.2: Display Devices"));

        // Adding Subsections to Section 1.2
        root->children[0]->children[1]->children.push_back(new Node("Subsection 1.2.1: CRT"));
        root->children[0]->children[1]->children.push_back(new Node("Subsection 1.2.2: LCD"));

        // Adding Sections to Chapter 2
        root->children[1]->children.push_back(new Node("Section 2.1: DDA Algorithm"));
        root->children[1]->children.push_back(new Node("Section 2.2: Bresenham Algorithm"));
    }

    // Recursive function to print the tree with indentation
    void printTree(Node* temp, int depth) {
        if (temp != nullptr) {
            // Provide indentation based on depth
            for (int i = 0; i < depth; i++) cout << "  ";
            
            cout << "|-- " << temp->label << endl;

            for (int i = 0; i < temp->children.size(); i++) {
                printTree(temp->children[i], depth + 1);
            }
        }
    }
};

int main() {
    BookTree myBook;
    myBook.createBook();
    
    cout << "--- Book Hierarchy ---" << endl;
    myBook.printTree(myBook.root, 0);

    return 0;
}