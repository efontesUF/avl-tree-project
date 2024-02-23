#include "../src/main.cpp"
#include "catch/catch_amalgamated.hpp"
#include <iostream>
#include <string>

using namespace std;

TEST_CASE("Incorrect commands", "[flag]") {
    AVLTree tree;

    SECTION("insert invalid name") {
        Command cmd;
        cmd.parseCommand("insert \"3ricF0ntes\" 00000001");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd.processCommand(tree);
        cmd.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "unsuccessful\n");
    };

    SECTION("insert invalid id (too short)") {
        Command cmd;
        cmd.parseCommand("insert \"Maria\" 123");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd.processCommand(tree);
        cmd.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "unsuccessful\n");
    };

    SECTION("insert invalid id (non-numeric)") {
        Command cmd;
        cmd.parseCommand("insert \"Neil\" abcdefgh");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd.processCommand(tree);
        cmd.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "unsuccessful\n");
    };

    SECTION("remove invalid id (non-numeric)") {
        Command cmd1;
        Command cmd2;
        cmd1.parseCommand("insert \"Algo\" 00000001");
        cmd2.parseCommand("remove 0000000a");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nunsuccessful\n");
    };

    SECTION("removeInorder too many arguments") {
        Command cmd1;
        Command cmd2;
        cmd1.parseCommand("insert \"Rithm\" 00000001");
        cmd2.parseCommand("removeInorder 2 3");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nunsuccessful\n");
    };
}

TEST_CASE("Edge cases", "[flag]") {
    AVLTree tree;

    SECTION("insert existing id") {
        Command cmd1;
        Command cmd2;
        cmd1.parseCommand("insert \"Original\" 00000001");
        cmd2.parseCommand("insert \"Copy\" 00000001");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nunsuccessful\n");
    };

    SECTION("remove nonexistent id") {
        Command cmd1;
        Command cmd2;
        Command cmd3;
        cmd1.parseCommand("insert \"Apple\" 00000001");
        cmd2.parseCommand("insert \"Orange\" 00000002");
        cmd3.parseCommand("remove 00000003");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);
        succ = cmd3.processCommand(tree);
        cmd3.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nsuccessful\nunsuccessful\n");
    };

    SECTION("removeInorder n > Nodes") {
        Command cmd1;
        Command cmd2;
        Command cmd3;
        cmd1.parseCommand("insert \"Blue\" 00000001");
        cmd2.parseCommand("insert \"Red\" 00000002");
        cmd3.parseCommand("removeInorder 6");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);
        succ = cmd3.processCommand(tree);
        cmd3.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nsuccessful\nunsuccessful\n");
    };
};

TEST_CASE("Four rotation cases", "[flag]") {
    AVLTree tree;

    SECTION("left rotation") {
        Command cmd1;
        Command cmd2;
        Command cmd3;
        Command cmd4;
        cmd1.parseCommand("insert \"A\" 00000001");
        cmd2.parseCommand("insert \"B\" 00000002");
        cmd3.parseCommand("insert \"C\" 00000003");
        cmd4.parseCommand("printPostorder");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);
        succ = cmd3.processCommand(tree);
        cmd3.printResult(succ);
        succ = cmd4.processCommand(tree);
        cmd4.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nsuccessful\nsuccessful\nA, C, B\n");
    };

    SECTION("right rotation") {
        Command cmd1;
        Command cmd2;
        Command cmd3;
        Command cmd4;
        cmd1.parseCommand("insert \"C\" 00000003");
        cmd2.parseCommand("insert \"B\" 00000002");
        cmd3.parseCommand("insert \"A\" 00000001");
        cmd4.parseCommand("printPostorder");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);
        succ = cmd3.processCommand(tree);
        cmd3.printResult(succ);
        succ = cmd4.processCommand(tree);
        cmd4.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nsuccessful\nsuccessful\nA, C, B\n");
    };

    SECTION("left right rotation") {
        Command cmd1;
        Command cmd2;
        Command cmd3;
        Command cmd4;
        cmd1.parseCommand("insert \"C\" 00000003");
        cmd2.parseCommand("insert \"A\" 00000001");
        cmd3.parseCommand("insert \"B\" 00000002");
        cmd4.parseCommand("printPostorder");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);
        succ = cmd3.processCommand(tree);
        cmd3.printResult(succ);
        succ = cmd4.processCommand(tree);
        cmd4.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nsuccessful\nsuccessful\nA, C, B\n");
    };

    SECTION("right left rotation") {
        Command cmd1;
        Command cmd2;
        Command cmd3;
        Command cmd4;
        cmd1.parseCommand("insert \"A\" 00000001");
        cmd2.parseCommand("insert \"C\" 00000003");
        cmd3.parseCommand("insert \"B\" 00000002");
        cmd4.parseCommand("printPostorder");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);
        succ = cmd3.processCommand(tree);
        cmd3.printResult(succ);
        succ = cmd4.processCommand(tree);
        cmd4.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nsuccessful\nsuccessful\nA, C, B\n");
    };
};

TEST_CASE("Three deletion cases", "[flag]") {
    AVLTree tree;

    SECTION("zero children") {
        Command cmd1;
        Command cmd2;
        Command cmd3;
        Command cmd4;
        Command cmd5;
        Command cmd6;
        cmd1.parseCommand("insert \"A\" 00000001");
        cmd2.parseCommand("insert \"B\" 00000002");
        cmd3.parseCommand("insert \"C\" 00000003");
        cmd4.parseCommand("insert \"D\" 00000004");
        cmd5.parseCommand("remove 00000001");
        cmd6.parseCommand("printInorder");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);
        succ = cmd3.processCommand(tree);
        cmd3.printResult(succ);
        succ = cmd4.processCommand(tree);
        cmd4.printResult(succ);
        succ = cmd5.processCommand(tree);
        cmd5.printResult(succ);
        succ = cmd6.processCommand(tree);
        cmd6.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nB, C, D\n");
    };

    SECTION("one child") {
        Command cmd1;
        Command cmd2;
        Command cmd3;
        Command cmd4;
        Command cmd5;
        Command cmd6;
        cmd1.parseCommand("insert \"A\" 00000001");
        cmd2.parseCommand("insert \"B\" 00000002");
        cmd3.parseCommand("insert \"C\" 00000003");
        cmd4.parseCommand("insert \"D\" 00000004");
        cmd5.parseCommand("remove 00000003");
        cmd6.parseCommand("printInorder");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);
        succ = cmd3.processCommand(tree);
        cmd3.printResult(succ);
        succ = cmd4.processCommand(tree);
        cmd4.printResult(succ);
        succ = cmd5.processCommand(tree);
        cmd5.printResult(succ);
        succ = cmd6.processCommand(tree);
        cmd6.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nA, B, D\n");
    };

    SECTION("two children") {
        Command cmd1;
        Command cmd2;
        Command cmd3;
        Command cmd4;
        Command cmd5;
        Command cmd6;
        cmd1.parseCommand("insert \"A\" 00000001");
        cmd2.parseCommand("insert \"B\" 00000002");
        cmd3.parseCommand("insert \"C\" 00000003");
        cmd4.parseCommand("insert \"D\" 00000004");
        cmd5.parseCommand("remove 00000002");
        cmd6.parseCommand("printInorder");

        stringstream output;
        streambuf* coutBuffer = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        bool succ = cmd1.processCommand(tree);
        cmd1.printResult(succ);
        succ = cmd2.processCommand(tree);
        cmd2.printResult(succ);
        succ = cmd3.processCommand(tree);
        cmd3.printResult(succ);
        succ = cmd4.processCommand(tree);
        cmd4.printResult(succ);
        succ = cmd5.processCommand(tree);
        cmd5.printResult(succ);
        succ = cmd6.processCommand(tree);
        cmd6.printResult(succ);

        cout.rdbuf(coutBuffer);

        REQUIRE(output);
        REQUIRE(output.str() == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nA, C, D\n");
    };
};

TEST_CASE("Insert large number of nodes", "[flag]") {
    AVLTree tree;
    vector<int> expectedOutput;
    int x = 200; // insert x numbers
    int y = 20;  // remove y numbers

    // insert x random numbers
    for (int i = 0; i < x; i++) {
        int randomInput = rand() % 100000000;
        if (count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0) {
            expectedOutput.push_back(randomInput);

            stringstream ss;
            ss << setfill('0') << setw(8) << randomInput;
            tree.insert(to_string(randomInput), ss.str());
        }
    }

    sort(expectedOutput.begin(), expectedOutput.end());

    // remove y random numbers
    for (int i = 0; i < y; i++) {
        int randomIndex = rand() % expectedOutput.size();
        expectedOutput.erase(expectedOutput.begin() + randomIndex);
        tree.removeInorder(randomIndex);
    }

    // create comma-separated string of numbers in expectedOutput
    stringstream ss;
    for (int i = 0; i < expectedOutput.size() - 1; i++) {
        ss << expectedOutput.at(i) << ", ";
    }
    ss << expectedOutput.back() << '\n';
    string expectedOutputList = ss.str();

    stringstream output;
    streambuf* coutBuffer = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    tree.printInorder();

    cout.rdbuf(coutBuffer);

    REQUIRE(output);
    REQUIRE(output.str() == expectedOutputList);
}
