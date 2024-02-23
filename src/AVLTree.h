#pragma once

#include <string>
#include <vector>

using namespace std;

class AVLTree {
    struct Node {
        string name;
        string id;
        int height;
        Node* left;
        Node* right;

        Node();
        Node(const string& name, const string& id);
    };

  private:
    Node* root = nullptr;
    Node* insertAt(Node* node, const string& name, const string& id, bool& isDupe);
    Node* removeNode(Node* node, const string& id, bool& removed);
    Node* minNode(Node* node);
    int getHeight(Node* node);
    int getBalance(Node* node);
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);
    void inorderHelper(Node* node, bool& first);
    void preorderHelper(Node* node, bool& first);
    void postorderHelper(Node* node, bool& first);
    Node* searchID(Node* node, const string& id);
    vector<Node*> searchName(Node* node, const string& name);
    Node* inorderTraverse(Node* node, int& n);
    void printHelper(int indent, Node* node); // debug function

  public:
    bool insert(const string& name, const string& id);
    bool remove(const string& id);
    bool searchID(const string& id);
    bool searchName(const string& name);
    void printInorder();
    void printPreorder();
    void printPostorder();
    void printLevelCount();
    bool removeInorder(int& n);
    void print(int indent); // debug function
};
