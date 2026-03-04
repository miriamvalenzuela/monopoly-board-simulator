#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

static const int MAX_SPACES = 40;

// -------------------------------
// Data class (NOT a struct)
// -------------------------------
class MonopolySpace {
public:
    string propertyName;
    string propertyColor;
    int value;
    int rent;

    MonopolySpace() {
        propertyName = "";
        propertyColor = "";
        value = 0;
        rent = 0;
    }

    MonopolySpace(string propertyName, string propertyColor, int value, int rent) {
        this->propertyName = propertyName;
        this->propertyColor = propertyColor;
        this->value = value;
        this->rent = rent;
    }

    bool isEqual(const MonopolySpace& other) const {
        return propertyName == other.propertyName;
    }

    void print() const {
        cout << propertyName << " | " << propertyColor
             << " | $" << value << " | Rent " << rent;
    }
};

// -------------------------------
// Template Node class (NOT a struct)
// -------------------------------
template <typename T>
class Node {
public:
    T data;
    Node<T>* nextNode;

    Node(T value) {
        data = value;
        nextNode = nullptr;
    }
};

// -------------------------------
// Template Circular Linked List class
// Spring 2026 version: traversable board
// -------------------------------
template <typename T>
class CircularLinkedList {
private:
    Node<T>* headNode;
    Node<T>* tailNode;

    // player cursor for traversal-based gameplay
    Node<T>* playerNode;

    int nodeCount;
    int passGoCount;

public:
    CircularLinkedList() {
        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;

        nodeCount = 0;
        passGoCount = 0;
    }

    // -------------------------------
    // Board Construction Policy (Reminder)
    // -------------------------------
    // Spaces are added during board construction BEFORE gameplay.
    // You choose how to construct the board:
    // - hardcode spaces, read from file, or generate programmatically
    // The only non-negotiable requirement:
    // - enforce MAX_SPACES
    // - maintain circular integrity
    // -------------------------------

    // -------------------------------
    // Core A: Add a Space with Capacity Enforcement
    // -------------------------------
    bool addSpace(const T& value) {
        if (nodeCount >= MAX_SPACES) {
            return false;
        }

        Node<T>* newNode = new Node<T>(value);

        if (headNode == nullptr) {
            headNode = newNode;
            tailNode = newNode;
            playerNode = newNode;
            tailNode->nextNode = headNode;
        } else {
            tailNode->nextNode = newNode;
            tailNode = newNode;
            tailNode->nextNode = headNode;
        }

        nodeCount++;
        return true;
    }

    // -------------------------------
    // Core B: Add Multiple Spaces at Once
    // -------------------------------
    int addMany(const vector<T>& values) {
        int added = 0;

        for (int i = 0; i < static_cast<int>(values.size()); i++) {
            if (!addSpace(values[i])) {
                break;
            }
            added++;
        }

        return added;
    }

    // -------------------------------
    // Core C: Traversal-Based Player Movement
    // -------------------------------
    void movePlayer(int steps) {
        if (headNode == nullptr || playerNode == nullptr || steps <= 0) {
            return;
        }

        for (int i = 0; i < steps; i++) {
            if (playerNode == tailNode) {
                passGoCount++;
            }
            playerNode = playerNode->nextNode;
        }
    }

    int getPassGoCount() {
        return passGoCount;
    }

    // -------------------------------
    // Core D: Controlled Board Display
    // -------------------------------
    void printFromPlayer(int count) {
        if (headNode == nullptr || playerNode == nullptr || count <= 0) {
            cout << "[Board is Empty!]" << endl;
            return;
        }

        Node<T>* current = playerNode;
        for (int i = 0; i < count; i++) {
            cout << " - ";
            current->data.print();
            cout << endl;
            current = current->nextNode;
        }
    }

    // Print full board once (one full cycle)
    void printBoardOnce() {
        if (headNode == nullptr) {
            cout << "Board is empty!" << endl;
            return;
        }

        Node<T>* currentNode = headNode;
        do {
            cout << " - ";
            currentNode->data.print();
            cout << endl;
            currentNode = currentNode->nextNode;
        } while (currentNode != headNode);
    }

    // -------------------------------
    // Advanced Option A (Level 1): removeByName
    // -------------------------------
    bool removeByName(string name) {
        // TODO:
        // - Delete FIRST matching node
        // - Must handle:
        //   - deleting head
        //   - deleting tail
        //   - deleting the only-node list
        // - Maintain circular link tail->next=head
        // - If playerNode points to deleted node, move playerNode to a safe node
        // - nodeCount--
        cout << "removeByName unwritten" << endl;
        return false;
    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    vector<string> findByColor(const string& color) {
        // TODO:
        // - Traverse ring exactly once
        // - Collect matching names in vector<string>
        // - Return matches
        cout << "findByColor unwritten" << endl;
        vector<string> matches;
        return matches;
    }

    // -------------------------------
    // Advanced Option B (Level 2): Mirror the Board (Circular Reversal)
    // -------------------------------
    void mirrorBoard() {
        // TODO:
        // - Reverse the direction of the circular list by reversing next pointers
        // - Preserve circular structure
        // - Correctly handle empty list and single-node list
        // - Player cursor must remain on the same logical space after reversal
        cout << "mirrorBoard unwritten" << endl;
    }

    // -------------------------------
    // Edge-case helper: countSpaces O(n)
    // -------------------------------
    int countSpaces() {
        // TODO:
        // - Must be O(n), traverse exactly once with correct stop condition
        // - Do NOT rely on nodeCount for this method
        cout << "countSpaces unwritten" << endl;
        return 0;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        // TODO:
        // - Safely delete all nodes
        // - Tip: if tailNode exists, break the cycle first: tailNode->nextNode = nullptr
        // - Then delete like a normal singly linked list
        cout << "clear unwritten" << endl;
    }
};

// -------------------------------
// Main: playable loop demo
// -------------------------------
int rollDice2to12() {
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    CircularLinkedList<MonopolySpace> board;

    // Tet movePlayer() + passGoCount
    // Temporary
    // TODO: Delete test in next commit.

    // Empty board should be safe
    {
        CircularLinkedList<MonopolySpace> emptyBoard;
        emptyBoard.movePlayer(5);
        cout << "Pass GO count: " << emptyBoard.getPassGoCount() << endl;
    }

    // Small board wrap + GO counting
    CircularLinkedList<MonopolySpace> testBoard;
    testBoard.addSpace(MonopolySpace("GO", "None", 0, 0));
    testBoard.addSpace(MonopolySpace("A", "Blue", 10, 1));
    testBoard.addSpace(MonopolySpace("B", "Red", 20, 2));

    cout << "\nStart Position (player starts at GO). Print 3 spaces:" << endl;
    testBoard.printFromPlayer(3);

    // Move 2 steps
    testBoard.movePlayer(2);
    cout << "Pass GO count: " << testBoard.getPassGoCount() << " (expected 0)" << endl;
    cout << "Now player should be at B. Print next 3 spaces:" << endl;
    testBoard.printFromPlayer(3);

    // Move 1 step: B -> GO (this crosses tail->head, should pass GO once)
    cout << "\nMove 1 step (B -> GO). Expected pass GO count becomes 1." << endl;
    testBoard.movePlayer(1);
    cout << "Pass GO count: " << testBoard.getPassGoCount() << " (expected 1)" << endl;
    cout << "Now player should be at GO. Print next 3 spaces:" << endl;
    testBoard.printFromPlayer(3);

    // Move 6 steps total from GO on a 3-space board:
    // Every 3 steps wraps once, so 6 steps wraps twice => should pass GO 2 more times.
    // Starting at GO: passing GO happens when crossing B->GO.
    // In 6 steps, cross B->GO exactly 2 times.
    cout << "\nMove 6 steps from GO on 3-space board." << endl;
    cout << "Expected additional passes: 2, so total should become 3." << endl;
    testBoard.movePlayer(6);
    cout << "Pass GO count: " << testBoard.getPassGoCount() << " (expected 3)" << endl;
    cout << "Print next 3 spaces from current position:" << endl;
    testBoard.printFromPlayer(3);

    board.printBoardOnce();

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    // You decide how to build the board:
    // - hardcode spaces, load from file, or generate spaces programmatically
    // The only requirement: never exceed MAX_SPACES and keep the list circular.
    //
    // Example (hardcoded) usage:
    // vector<MonopolySpace> spaces;
    // spaces.push_back(MonopolySpace("GO","None",0,0));
    // ...
    // board.addMany(spaces);
    //
    // NOTE: This starter calls addSpace once to show the intended API,
    // but your final submission should build a meaningful board.
    board.addSpace(MonopolySpace("GO", "None", 0, 0));

    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
    for (int turn = 1; turn <= 10; turn++) {
        int roll = rollDice2to12();
        cout << "\nTurn " << turn << " | Rolled: " << roll << endl;

        board.movePlayer(roll);

        cout << "Board view from player (next 5 spaces):" << endl;
        board.printFromPlayer(5);

        cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
    }

    // -------------------------------
    // Advanced Feature Demos (students choose path)
    // -------------------------------
    // Option A examples:
    // board.removeByName("Baltic Avenue");
    // vector<string> brownProps = board.findByColor("Brown");
    //
    // Option B example:
    // board.mirrorBoard();

    return 0;
}
