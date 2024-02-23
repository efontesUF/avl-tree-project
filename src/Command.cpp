#include "Command.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

Command::Command() : name(), options() {}

bool isValidName(const string& name) {
    for (const char& c : name) {
        if (!isalpha(c) && !isspace(c))
            return false;
    }

    return true;
}

bool isValidID(const string& id) {
    if (id.length() != 8)
        return false;

    for (const char& n : id) {
        if (!isdigit(n))
            return false;
    }

    return true;
}

Command Command::parseCommand(const string& line) {
    istringstream iss(line);
    iss >> name;

    string option;
    while (iss >> quoted(option))
        options.push_back(option);

    return (*this);
}

bool Command::processCommand(AVLTree& tree) {
    if (name == "insert") {
        if (options.size() != 2)
            return false;

        string name = options[0];
        string id = options[1];

        if (!isValidName(name) || !isValidID(id))
            return false;

        return tree.insert(name, id);

    } else if (name == "remove") {
        if (options.size() != 1)
            return false;

        string id = options[0];

        if (!isValidID(id))
            return false;

        return tree.remove(id);

    } else if (name == "search") {
        if (options.size() != 1)
            return false;

        string key = options[0];

        if (isValidID(key))
            return tree.searchID(key);
        if (isValidName(key))
            return tree.searchName(key);

        return false;

    } else if (name == "printInorder") {
        tree.printInorder();
    } else if (name == "printPreorder") {
        tree.printPreorder();
    } else if (name == "printPostorder") {
        tree.printPostorder();
    } else if (name == "printLevelCount") {
        tree.printLevelCount();
    } else if (name == "removeInorder") {
        if (options.size() != 1)
            return false;

        int n = stoi(options[0]);

        return tree.removeInorder(n);

    } else {
        return false;
    }

    return true;
}

void Command::printResult(bool succ) {
    bool isPrintCmd = name.substr(0, 5) == "print";
    bool isSearchCmd = name.substr(0, 6) == "search";

    if (succ && !isPrintCmd && !isSearchCmd) {
        cout << "successful" << endl;
    } else if (!succ) {
        cout << "unsuccessful" << endl;
    }
}
