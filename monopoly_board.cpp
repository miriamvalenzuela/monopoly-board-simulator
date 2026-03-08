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
            cout << "Board is Empty!" << endl;
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
            cout << "Board is Empty!" << endl;
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
    bool removeByName(const string& name) {
        if (headNode == nullptr) {
            return false;
        }

        // Only-node list
        if (headNode == tailNode) {
            if (headNode->data.propertyName == name) {
                delete headNode;
                headNode = nullptr;
                tailNode = nullptr;
                playerNode = nullptr;
                nodeCount--;
                return true;
            }
            return false;
        }

        Node<T>* prev = tailNode;
        Node<T>* current = headNode;

        do {
            if (current->data.propertyName == name) {

                // If player is on the node being deleted, move player first
                if (playerNode == current) {
                    playerNode = current->nextNode;
                }

                // Deleting head
                if (current == headNode) {
                    headNode = headNode->nextNode;
                    tailNode->nextNode = headNode;
                    prev->nextNode = headNode;
                }
                // Deleting tail
                else if (current == tailNode) {
                    tailNode = prev;
                    tailNode->nextNode = headNode;
                    prev->nextNode = headNode;
                }
                // Deleting middle
                else {
                    prev->nextNode = current->nextNode;
                }

                delete current;
                nodeCount--;
                return true;
            }

            prev = current;
            current = current->nextNode;
        } while (current != headNode);

        return false;
    }

    // -------------------------------
    // Advanced Option A (Level 1): findByColor
    // -------------------------------
    vector<string> findByColor(const string& color) {
        vector<string> matches;

        if (headNode == nullptr) {
            return matches;
        }

        Node<T>* current = headNode;
        do {
            if (current->data.propertyColor == color) {
                matches.push_back(current->data.propertyName);
            }
            current = current->nextNode;
        } while (current != headNode);

        return matches;
    }

    // -------------------------------
    // Edge-case helper: countSpaces O(n)
    // -------------------------------
    int countSpaces() {
        if (headNode == nullptr) {
            return 0;
        }

        int count = 1;                 // count the head
        Node<T>* current = headNode->nextNode;

        while (current != headNode) {  // stop when looping back to head
            count++;
            current = current->nextNode;
        }

        return count;
    }

    // -------------------------------
    // Cleanup
    // -------------------------------
    void clear() {
        if (headNode == nullptr) {
            return;
        }

        // Break cycle first
        tailNode->nextNode = nullptr;

        Node<T>* current = headNode;
        while (current != nullptr) {
            Node<T>* deleteThis = current;
            current = current->nextNode;
            delete deleteThis;
        }

        headNode = nullptr;
        tailNode = nullptr;
        playerNode = nullptr;
        nodeCount = 0;
        passGoCount = 0;
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

    // -------------------------------
    // Board Construction Phase
    // -------------------------------
    vector<MonopolySpace> spaces;
    spaces.push_back(MonopolySpace("GO", "None", 0, 0));

    for (int i = 1; i < MAX_SPACES; i++) {
        string name = "Space " + to_string(i);
        string color = (i % 4 == 0) ? "Red" :
                       (i % 4 == 1) ? "Blue" :
                       (i % 4 == 2) ? "Green" : "Yellow";
        spaces.push_back(MonopolySpace(name, color, i * 10, i * 2));
    }

    cout << "Created " << spaces.size() << " spaces to add." << endl;

    int added = board.addMany(spaces);
    cout << "Built board with " << added << " spaces." << endl;
    cout << "countSpaces() check: " << board.countSpaces() << " (expected " << added << ")" << endl;

    bool extra = board.addSpace(MonopolySpace("Overflow Space", "None", 999, 99));
    cout << "Attempt to add 41st space returned: " << (extra ? "true" : "false") << " (expected false)" << endl;

    cout << "\nFirst 10 spaces from starting player position:" << endl;
    board.printFromPlayer(10);

    // -------------------------------
    // Playable Traversal Loop
    // -------------------------------
    for (int turn = 1; turn <= 10; turn++) {
        int roll = rollDice2to12();
        cout << "\nTurn " << turn << " | Rolled: " << roll << endl;

        board.movePlayer(roll);

        cout << "Landed on:" << endl;
        board.printFromPlayer(1);

        cout << "Board view from player (next 5 spaces):" << endl;
        board.printFromPlayer(5);

        cout << "Times passed GO so far: " << board.getPassGoCount() << endl;
    }

    // -------------------------------
    // Advanced Feature Demos (Option A)
    // -------------------------------
    cout << "\n===== Advanced Demo: findByColor(\"Red\") =====" << endl;
    vector<string> reds = board.findByColor("Red");
    cout << "Found " << reds.size() << " red spaces." << endl;
    cout << "First few red spaces:" << endl;
    for (int i = 0; i < static_cast<int>(reds.size()) && i < 5; i++) {
        cout << " - " << reds.at(i) << endl;
    }

    cout << "\n===== Advanced Demo: removeByName(\"Space 20\") =====" << endl;
    bool removed = board.removeByName("Space 20");
    cout << "removeByName(\"Space 20\") returned: " << (removed ? "true" : "false") << " (expected true)" << endl;
    cout << "countSpaces() after removal: " << board.countSpaces() << " (expected 39)" << endl;

    cout << "Print 8 spaces from player (board should still wrap correctly):" << endl;
    board.printFromPlayer(8);

    cout << "\n===== Advanced Demo: remove edge cases on a tiny board =====" << endl;
    CircularLinkedList<MonopolySpace> tiny;
    tiny.addSpace(MonopolySpace("GO", "None", 0, 0));
    tiny.addSpace(MonopolySpace("A", "Blue", 10, 1));
    tiny.addSpace(MonopolySpace("B", "Red", 20, 2));

    cout << "Tiny board before deleting head (printing 5):" << endl;
    tiny.printFromPlayer(5);

    cout << "Delete head GO: " << (tiny.removeByName("GO") ? "true" : "false") << endl;
    cout << "Tiny board after deleting head (printing 5):" << endl;
    tiny.printFromPlayer(5);

    cout << "Delete tail B: " << (tiny.removeByName("B") ? "true" : "false") << endl;
    cout << "Tiny board after deleting tail (printing 5):" << endl;
    tiny.printFromPlayer(5);

    cout << "\nEnd of demo." << endl;
    return 0;
}
