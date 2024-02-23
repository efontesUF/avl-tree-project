#include "AVLTree.h"
#include "Command.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main() {
    vector<Command> cmdList;
    AVLTree leEpicTree;

    // read one line as the number of commands
    int numCommands;
    cin >> numCommands;
    cin.ignore();

    // populate command list
    for (int i = 0; i < numCommands; i++) {
        string line;
        getline(cin, line);
        Command cmd;
        cmd.parseCommand(line);
        cmdList.push_back(cmd);
    }

    // do stuff with commands
    for (auto& cmd : cmdList) {
        bool succ = cmd.processCommand(leEpicTree);
        cmd.printResult(succ);
    }

    // print entire tree for debugging
    // leEpicTree.print(1);

    return 0;
}
