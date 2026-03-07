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

// Test removeByName()
// TEMPORARY
// TODO: Delete tests in next commit

// Empty board (should return false, no crash)
{
    CircularLinkedList<MonopolySpace> empty;
    cout << "\n[Test 1] Empty board removeByName(\"GO\"):" << endl;
    bool result = empty.removeByName("GO");
    cout << "Returned: " << (result ? "true" : "false") << " (expected false)" << endl;

    cout << "Printing from player (should show empty message):" << endl;
    empty.printFromPlayer(3);
}

// Only-node list delete (head==tail)
{
    CircularLinkedList<MonopolySpace> one;
    one.addSpace(MonopolySpace("GO", "None", 0, 0));

    cout << "\n[Test 2] Only-node list before delete (print 3):" << endl;
    one.printFromPlayer(3);

    cout << "Removing \"GO\" (expected true):" << endl;
    bool result = one.removeByName("GO");
    cout << "Returned: " << (result ? "true" : "false") << " (expected true)" << endl;

    cout << "After delete, printFromPlayer(3) should show empty message:" << endl;
    one.printFromPlayer(3);
}

// Delete head node in multi-node list
{
    CircularLinkedList<MonopolySpace> list;
    list.addSpace(MonopolySpace("GO", "None", 0, 0));      // head
    list.addSpace(MonopolySpace("A", "Blue", 10, 1));
    list.addSpace(MonopolySpace("B", "Red", 20, 2));       // tail

    cout << "\n[Test 3] Multi-node list before deleting head (print 5):" << endl;
    list.printFromPlayer(5);

    cout << "Removing head \"GO\" (expected true):" << endl;
    bool result = list.removeByName("GO");
    cout << "Returned: " << (result ? "true" : "false") << " (expected true)" << endl;

    cout << "After delete head, print 5 from player (should NOT show GO):" << endl;
    list.printFromPlayer(5);
}

// Delete tail node in multi-node list
{
    CircularLinkedList<MonopolySpace> list;
    list.addSpace(MonopolySpace("GO", "None", 0, 0));
    list.addSpace(MonopolySpace("A", "Blue", 10, 1));
    list.addSpace(MonopolySpace("B", "Red", 20, 2));       // tail

    cout << "\n[Test 4] List before deleting tail (print 5):" << endl;
    list.printFromPlayer(5);

    cout << "Removing tail \"B\" (expected true):" << endl;
    bool result = list.removeByName("B");
    cout << "Returned: " << (result ? "true" : "false") << " (expected true)" << endl;

    cout << "After delete tail, print 5 (should wrap between GO and A):" << endl;
    list.printFromPlayer(5);
}

// Delete middle node in multi-node list
{
    CircularLinkedList<MonopolySpace> list;
    list.addSpace(MonopolySpace("GO", "None", 0, 0));
    list.addSpace(MonopolySpace("A", "Blue", 10, 1));      // middle
    list.addSpace(MonopolySpace("B", "Red", 20, 2));

    cout << "\n[Test 5] List before deleting middle (print 6):" << endl;
    list.printFromPlayer(6);

    cout << "Removing middle \"A\" (expected true):" << endl;
    bool result = list.removeByName("A");
    cout << "Returned: " << (result ? "true" : "false") << " (expected true)" << endl;

    cout << "After delete middle, print 6 (should not show A):" << endl;
    list.printFromPlayer(6);
}

// Remove player's current node safety
{
    CircularLinkedList<MonopolySpace> list;
    list.addSpace(MonopolySpace("GO", "None", 0, 0));   // player starts here
    list.addSpace(MonopolySpace("A", "Blue", 10, 1));
    list.addSpace(MonopolySpace("B", "Red", 20, 2));

    cout << "\n[Test 6] Player safety test before delete (print 4):" << endl;
    list.printFromPlayer(4);

    cout << "Removing player's current node \"GO\" (expected true):" << endl;
    bool result = list.removeByName("GO");
    cout << "Returned: " << (result ? "true" : "false") << " (expected true)" << endl;

    cout << "After removing GO, print 4 should still work (player should be on a safe node):" << endl;
    list.printFromPlayer(4);
}

// Remove a name that does not exist
{
    CircularLinkedList<MonopolySpace> list;
    list.addSpace(MonopolySpace("GO", "None", 0, 0));
    list.addSpace(MonopolySpace("A", "Blue", 10, 1));
    list.addSpace(MonopolySpace("B", "Red", 20, 2));

    cout << "\n[Test 7] Removing non-existent \"Z\" (expected false):" << endl;
    bool result = list.removeByName("Z");
    cout << "Returned: " << (result ? "true" : "false") << " (expected false)" << endl;

    cout << "List should still be intact (print 4):" << endl;
    list.printFromPlayer(4);
}

    board.printBoardOnce();

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

    int added = board.addMany(spaces);
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

    // Advanced Option A
    vector<string> reds = board.findByColor("Red");
    cout << "Red spaces: " << reds.size() << endl;

    return 0;
}
