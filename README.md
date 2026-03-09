# CS210 Programming Assignment
## Monopoly Board Simulator (Spring 2026)

### Overview
This project implements a Monopoly-style game board using a **circular linked list**. The circular structure is used for both storage and gameplay traversal. A single player moves around the board by following node pointers, can pass GO multiple times, and interacts with the space landed on through printed output.

### This assignment emphasizes
- Correct implementation of a circular linked list
- Careful pointer management under constraints
- Traversal-based logic instead of index-based shortcuts
- Professional development practices using GitHub

---

## Board Constraints (40-space limit)
- The Monopoly board has a maximum of **40 spaces** (`MAX_SPACES = 40`).
- The linked list must never exceed 40 nodes.
- Once the board reaches capacity, additional insertions must be rejected cleanly **without** corrupting the list.

---

## How to Build and Run
### Build
From the project directory:
- `g++ -std=c++17 monopoly_board.cpp -o monopoly_board`

### Run
- `./monopoly_board`

---

## Data Structures Used

### `MonopolySpace` (data class)
Represents one board space:
- `propertyName` (string)
- `propertyColor` (string)
- `value` (int)
- `rent` (int)

Key methods:
- `print()` displays a readable line for a space.

### `Node<T>` (linked list node)
Each node stores:
- `data` (a `MonopolySpace`)
- `nextNode` pointer to the next node

### `CircularLinkedList<T>` (the board "engine")
The board is a circular linked list with three important pointers:
- `headNode`: first node on the board (GO in this project)
- `tailNode`: last node on the board
- `playerNode`: the player's current position (cursor)

Circular rule:
- `tailNode->nextNode` always points back to `headNode`, forming a ring.

---

## Complete Function List

### MonopolySpace
- `MonopolySpace()`
  - Default constructor (safe empty values).
- `MonopolySpace(string propertyName, string propertyColor, int value, int rent)`
  - Creates a fully defined space.
- `bool isEqual(const MonopolySpace& other) const`
  - Compares spaces by name.
- `void print() const`
  - Prints: `Name | Color | $Value | Rent Rent`

### CircularLinkedList<T>
#### Core Requirements
- `bool addSpace(const T& value)`
  - Adds a new node to the tail.
  - Enforces the **40-space limit** (returns `false` when full).
  - Maintains circular integrity (`tail->next = head`).
- `int addMany(const vector<T>& values)`
  - Adds spaces sequentially until the board is full.
  - Stops exactly at capacity and returns number added.
- `void movePlayer(int steps)`
  - Moves the player forward node-by-node for `steps`.
  - Wraps automatically because the list is circular.
  - Tracks passing GO when crossing from `tailNode` back to `headNode`.
- `void printFromPlayer(int count)`
  - Prints exactly `count` spaces starting from `playerNode`.
  - Uses a fixed loop count to avoid infinite loops.
- `void printBoardOnce()`
  - Prints the entire board exactly once around the ring (one full cycle).
- `int getPassGoCount()`
  - Returns how many times the player passed GO.

#### Advanced Option A Features
- `bool removeByName(const string& name)`
  - Deletes the **first** matching space by name.
  - Correctly handles:
    - deleting the head node
    - deleting the tail node
    - deleting the only-node list
  - Preserves circular structure and keeps `playerNode` safe if it was deleted.
- `vector<string> findByColor(const string& color)`
  - Traverses the ring exactly once and returns matching space names.

#### Edge-Case / Helper Functions
- `int countSpaces()`
  - O(n) traversal that counts nodes by walking the ring exactly once.
  - Does not rely on `nodeCount`.
- `void clear()`
  - Safely deletes all nodes:
    - breaks the circular link first
    - deletes like a normal singly linked list
    - resets pointers and counters

---

## Traversal and Movement Logic (no indexing shortcuts)
- The board is a ring. The last node points back to the first node:
  - `tailNode->nextNode == headNode`
- The player’s location is stored as a pointer (`playerNode`) to a node in the ring.
- To move `steps` spaces, the program advances the pointer one node at a time:
  - repeat `steps` times: `playerNode = playerNode->nextNode`
- Wrap-around requires no special indexing logic because following `nextNode` from the tail automatically returns to the head.
- Passing GO is counted when a step crosses from the tail back to the head:
  - if the player is currently on `tailNode` and takes a step, `passGoCount` increments.

---

## Program Demonstration (main)
`main()` demonstrates:
1) **Board construction phase**
  - Generates 40 spaces (GO + Space 1..39)
  - Adds them using `addMany`
  - Attempts a 41st insertion to prove capacity enforcement
2) **Playable traversal loop**
  - 10 turns
  - Dice roll (2–12)
  - Move player
  - Print the landed space and next 5 spaces
  - Display how many times GO has been passed
3) **Advanced demos**
  - Uses `findByColor("Red")`
  - Uses `removeByName("Space 20")`
  - Demonstrates remove edge cases on a tiny board

---
