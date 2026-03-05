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

    // Test: Build a meaningful 40-space board using addMany()
    // Temporary
    // TODO: Delete test in next commit

    vector<MonopolySpace> spaces;

    // Always add GO first
    spaces.push_back(MonopolySpace("GO", "None", 0, 0));

    // Create 39 more spaces (Space 1 ... Space 39)
    for (int i = 1; i < MAX_SPACES; i++) {
        string name = "Space " + to_string(i);

        // Give repeating colors so findByColor works later
        string color;
        if (i % 4 == 0) color = "Red";
        else if (i % 4 == 1) color = "Blue";
        else if (i % 4 == 2) color = "Green";
        else color = "Yellow";

        int value = i * 10;
        int rent = i * 2;

        spaces.push_back(MonopolySpace(name, color, value, rent));
    }

    cout << "Created " << spaces.size() << " spaces in a vector (expected 40)." << endl;

    int added = board.addMany(spaces);
    cout << "board.addMany(...) returned: " << added << " (expected 40)" << endl;

    // Confirm board is full by trying to add one more space
    bool extraAdd = board.addSpace(MonopolySpace("Overflow Space", "None", 999, 99));
    cout << "Trying to add a 41st space returned: "
         << (extraAdd ? "true" : "false") << " (expected false)" << endl;

    board.printBoardOnce();

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    spaces.push_back(MonopolySpace("GO", "None", 0, 0));

    for (int i = 1; i < MAX_SPACES; i++) {
        string name = "Space " + to_string(i);
        string color = (i % 4 == 0) ? "Red" :
                       (i % 4 == 1) ? "Blue" :
                       (i % 4 == 2) ? "Green" : "Yellow";
        spaces.push_back(MonopolySpace(name, color, i * 10, i * 2));
    }

    cout << "Built board with " << added << " spaces." << endl;

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
