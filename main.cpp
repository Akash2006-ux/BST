//
// Created by akash on 11/5/2026.
//


#include <iostream>
#include <string>
#include <queue>

// A single node of the binary search tree.
// This stores an integer value and pointers to its left and right children
struct Node {
    int data;
    Node* left;
    Node* right;

    // This is the constructor initializes the value and nulls out both children
    explicit Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// This encapsulates all BST operations behind a small public interface
// This the root pointer is kept private; helper methods operate on nodes
// This also recursively (or iteratively, where convenient)
class BST {
private:
    Node* root;  // This is the root of the tree, nullptr when the tree is empty

    // This inserts a new node at the first null child slot
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);      // Found insertion point.
        }

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        // value == node->data: duplicate, don't do anything

        return node;
    }

    // This is the Min-Value helper
    Node* minValueNode(Node* node) {
        while (node != nullptr && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // This is to delete the helper
    Node* deleteValue(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;               // This is to show value not present
        }

        if (value < node->data) {
            node->left = deleteValue(node->left, value);
        } else if (value > node->data) {
            node->right = deleteValue(node->right, value);
        } else {
            // This is to show it is found the node to delete
            if (node->left == nullptr) {
                Node* rightChild = node->right;
                delete node;
                return rightChild;
            }

            if (node->right == nullptr) {
                Node* leftChild = node->left;
                delete node;
                return leftChild;
            }

            // The two children: use in-order successor which is the samllest in right sub-tree
            Node* successor = minValueNode(node->right);
            node->data = successor->data;
            node->right = deleteValue(node->right, successor->data);
        }

        return node;
    }

    // This is the BST lookup: descend left for smaller values, right for
    // larger values, it also returns true as soon as the value is found.
    bool search(Node* node, int value) const {
        while (node != nullptr) {
            if (value == node->data) {
                return true;
            } else if (value < node->data) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }

    // Each traversal prints values separated by a single space,
    // including a trailing space after the last value

    // Left -> Root -> Right
    void inorder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        std::cout << node->data << ' ';
        inorder(node->right);
    }

    // Root -> Left -> Right
    void preorder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        std::cout << node->data << ' ';
        preorder(node->left);
        preorder(node->right);
    }

    // Left -> Right -> Root
    void postorder(Node* node) const {
        if (node == nullptr) {
            return;
        }
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << ' ';
    }

    // This is the BFS process
    void levelOrder(Node* node) const {
        if (node == nullptr) {
            return;
        }

        std::queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            std::cout << current->data << ' ';

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }


    // This recursively frees every node, children must be freed before the
    // parent, so a post-order walk is used.
    void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    // This is an empty tree upon construction
    BST() : root(nullptr) {}

    // This releases all allocated nodes when the BST goes out of scope
    ~BST() {
        destroy(root);
    }

    // This is the public wrappers that hide the recursive/iterative helpers and
    // supply the current root pointer
    void insert(int value) {
        root = insert(root, value);
    }

    void deleteValue(int value) {
        root = deleteValue(root, value);
    }

    bool search(int value) const {
        return search(root, value);
    }


    // For an empty tree, only the newline is printed, which produces
    // the empty line

    void inorder() const {
        inorder(root);
        std::cout << '\n';
    }

    void preorder() const {
        preorder(root);
        std::cout << '\n';
    }

    void postorder() const {
        postorder(root);
        std::cout << '\n';
    }

    void levelOrder() const {
        levelOrder(root);
        std::cout << '\n';
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int numberOfQueries;
    std::cin >> numberOfQueries;

    BST tree;

    // This reads and dispatch each query to the appropriate BST operation
    for (int i = 0; i < numberOfQueries; ++i) {
        std::string command;
        std::cin >> command;

        if (command == "INSERT") {
            int value;
            std::cin >> value;
            tree.insert(value);
        } else if (command == "DELETE") {
            int value;
            std::cin >> value;
            tree.deleteValue(value);
        } else if (command == "SEARCH") {
            int value;
            std::cin >> value;
            std::cout << (tree.search(value) ? "True" : "False") << '\n';
        } else if (command == "INORDER") {
            tree.inorder();
        } else if (command == "PREORDER") {
            tree.preorder();
        } else if (command == "POSTORDER") {
            tree.postorder();
        } else if (command == "LEVELORDER") {
            tree.levelOrder();
        }
        // The unknown commands are silently ignored
    }

    return 0;
}