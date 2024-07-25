#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insert(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }
        return node;
    }

    Node* search(Node* node, int val) {
        if (node == nullptr || node->data == val) {
            return node;
        }
        if (val < node->data) {
            return search(node->left, val);
        }
        return search(node->right, val);
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteNode(Node* node, int val) {
        if (node == nullptr) {
            return node;
        }
        if (val < node->data) {
            node->left = deleteNode(node->left, val);
        } else if (val > node->data) {
            node->right = deleteNode(node->right, val);
        } else {
            // Node with only one child or no child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest in the right subtree)
            Node* temp = findMin(node->right);

            // Copy the inorder successor's content to this node
            node->data = temp->data;

            // Delete the inorder successor
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int val) {
        root = insert(root, val);
    }

    bool search(int val) {
        return search(root, val) != nullptr;
    }

    void deleteNode(int val) {
        root = deleteNode(root, val);
    }

    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    cout << "Inorder traversal of the given tree: ";
    bst.inorderTraversal();

    cout << "Delete 20\n";
    bst.deleteNode(20);
    cout << "Inorder traversal of the modified tree: ";
    bst.inorderTraversal();

    cout << "Delete 30\n";
    bst.deleteNode(30);
    cout << "Inorder traversal of the modified tree: ";
    bst.inorderTraversal();

    cout << "Delete 50\n";
    bst.deleteNode(50);
    cout << "Inorder traversal of the modified tree: ";
    bst.inorderTraversal();

    cout << "Search 40: " << (bst.search(40) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (bst.search(100) ? "Found" : "Not Found") << endl;

    return 0;
}
