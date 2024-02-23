#include "AVLTree.h"
#include <iostream>

using namespace std;

// default node constructor
AVLTree::Node::Node() : name(""), id(""), height(1), left(nullptr), right(nullptr) {}

// parameterized node constructor
AVLTree::Node::Node(const string& name, const string& id)
    : name(name), id(id), height(1), left(nullptr), right(nullptr) {}

// helper function to get the height of a node
int AVLTree::getHeight(AVLTree::Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

// helper function to get the balance factor of a node
int AVLTree::getBalance(AVLTree::Node* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLTree::Node* AVLTree::minNode(Node* node) {
    Node* temp = node;
    while (temp->left != nullptr)
        temp = temp->left;

    return temp;
}

// helper function to perform a right rotation
AVLTree::Node* AVLTree::rightRotate(Node* node) {
    Node* nodeLeft = node->left;
    Node* nodeLeftRight = nodeLeft->right;

    // right rotate
    nodeLeft->right = node;
    node->left = nodeLeftRight;

    // update heights
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    nodeLeft->height =
        1 + max(getHeight(nodeLeft->left), getHeight(nodeLeft->right));

    // return new root
    return nodeLeft;
}

// helper function to perform a left rotation
AVLTree::Node* AVLTree::leftRotate(Node* node) {
    Node* nodeRight = node->right;
    Node* nodeRightLeft = nodeRight->left;

    // left rotate
    nodeRight->left = node;
    node->right = nodeRightLeft;

    // update heights
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    nodeRight->height =
        1 + max(getHeight(nodeRight->left), getHeight(nodeRight->right));

    // return new root
    return nodeRight;
}

AVLTree::Node* AVLTree::insertAt(Node* node, const string& name,
                                 const string& id, bool& isDupe) {
    /* normal BST insertion */
    if (node == nullptr)
        return (new Node(name, id));

    if (id < node->id)
        node->left = insertAt(node->left, name, id, isDupe);
    else if (id > node->id)
        node->right = insertAt(node->right, name, id, isDupe);
    else { // duplicate node
        isDupe = true;
        return node;
    }

    // update node height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    /* handle unbalanced tree */
    int balance = getBalance(node);

    // left left
    if (balance > 1 && id < node->left->id)
        return rightRotate(node);

    // right right
    if (balance < -1 && id > node->right->id)
        return leftRotate(node);

    // left right
    if (balance > 1 && id > node->left->id) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // right left
    if (balance < -1 && id < node->right->id) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLTree::Node* AVLTree::removeNode(Node* node, const string& id, bool& removed) {
    if (node == nullptr) {
        removed = false;
        return nullptr;
    }

    if (id < node->id) {
        node->left = removeNode(node->left, id, removed);
        return node;
    } else if (id > node->id) {
        node->right = removeNode(node->right, id, removed);
        return node;
    }

    // node was found so set removed to true
    removed = true;

    // one child empty case
    if (node->left == nullptr) {
        Node* temp = node->right;
        delete node;
        return temp;
    } else if (node->right == nullptr) {
        Node* temp = node->left;
        delete node;
        return temp;
    } else { // two child case
        // find successor and parent
        Node* successorParent = node;
        Node* successor = node->right;
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        // copy successor data to node
        node->id = successor->id;
        node->name = successor->name;

        // delete successor
        if (successorParent != node)
            successorParent->left = successor->right;
        else
            successorParent->right = successor->right;

        delete successor;
        return node;
    }

    return node;
}

// helper function for inorder traversal
void AVLTree::inorderHelper(Node* node, bool& first) {
    if (node == nullptr)
        return;

    inorderHelper(node->left, first);
    if (!first)
        cout << ", ";
    cout << node->name;
    first = false;
    inorderHelper(node->right, first);
}

// helper function for preorder traversal
void AVLTree::preorderHelper(Node* node, bool& first) {
    if (node == nullptr)
        return;

    if (!first)
        cout << ", ";
    cout << node->name;
    first = false;
    preorderHelper(node->left, first);
    preorderHelper(node->right, first);
}

// helper function for postorder traversal
void AVLTree::postorderHelper(Node* node, bool& first) {
    if (node == nullptr)
        return;

    postorderHelper(node->left, first);
    postorderHelper(node->right, first);
    if (!first)
        cout << ", ";
    cout << node->name;
    first = false;
}

AVLTree::Node* AVLTree::searchID(Node* node, const string& id) {
    if (node == nullptr)
        return nullptr;

    if (id < node->id)
        return searchID(node->left, id);
    else if (id > node->id)
        return searchID(node->right, id);
    else
        return node;
}

vector<AVLTree::Node*> AVLTree::searchName(Node* node, const string& name) {
    vector<Node*> names;

    if (node == nullptr)
        return names;

    if (name == node->name)
        names.push_back(node);

    vector<Node*> leftNames = searchName(node->left, name);
    names.insert(names.end(), leftNames.begin(), leftNames.end());

    vector<Node*> rightNames = searchName(node->right, name);
    names.insert(names.end(), rightNames.begin(), rightNames.end());

    return names;
}

AVLTree::Node* AVLTree::inorderTraverse(Node* node, int& n) {
    if (node == nullptr)
        return nullptr;

    Node* nodeLeft = inorderTraverse(node->left, n);
    if (nodeLeft != nullptr)
        return nodeLeft;

    if (--n == 0)
        return node;

    return inorderTraverse(node->right, n);
};

void AVLTree::printHelper(int indent, Node* node) {
    int i;

    if (node != NULL) {
        printHelper(indent + 1, node->right);
        cout << endl;
        if (node == root)
            cout << "Root -> ";
        for (i = 0; i < indent && node != root; i++)
            cout << "        ";
        cout << node->name;
        printHelper(indent + 1, node->left);
    }
}

void AVLTree::print(int indent) {
    printHelper(indent, root);
}

bool AVLTree::insert(const string& name, const string& id) {
    bool isDupe = false;
    Node* result = insertAt(root, name, id, isDupe);

    if (isDupe == false)
        root = result;

    return !isDupe;
}

bool AVLTree::remove(const string& id) {
    bool removed = false;
    root = removeNode(root, id, removed);
    return removed;
}

bool AVLTree::searchID(const string& id) {
    Node* result = searchID(root, id);

    if (result == nullptr)
        return false;

    cout << result->name << endl;
    return true;
}

bool AVLTree::searchName(const string& name) {
    vector<Node*> names = searchName(root, name);

    if (names.empty())
        return false;

    for (const auto& node : names)
        cout << node->id << endl;

    return true;
}

void AVLTree::printInorder() {
    bool first = true;
    inorderHelper(root, first);
    cout << endl;
}

void AVLTree::printPreorder() {
    bool first = true;
    preorderHelper(root, first);
    cout << endl;
}

void AVLTree::printPostorder() {
    bool first = true;
    postorderHelper(root, first);
    cout << endl;
}

void AVLTree::printLevelCount() {
    int levelCount = getHeight(root);
    cout << levelCount;
    cout << endl;
}

bool AVLTree::removeInorder(int& n) {
    Node* node = inorderTraverse(root, ++n);
    if (node == nullptr)
        return false;

    remove(node->id);
    return true;
}
