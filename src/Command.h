#pragma once

#include "AVLTree.h"
#include <string>
#include <vector>

using namespace std;

struct Command {
    string name;
    vector<string> options;

    Command();
    Command parseCommand(const string& line);
    bool processCommand(AVLTree& tree);
    void printResult(bool succ);
};
