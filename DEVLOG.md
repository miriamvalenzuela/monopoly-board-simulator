# Developer Log (DEVLOG.md)
## Monopoly Board Simulator (Spring 2026)

Minimum **6 entries** required.

Each entry must document learning and reasoning. Fabricated bugs are not expected.

---

## Allowed Entry Types
Each entry may be one of the following:

1) **Bug Fix Entry**
- The issue encountered.
- Error messages or symptoms.
- Attempts made.
- Final resolution.

2) **Edge Case / Testing Entry**
- A failure discovered through testing.
- The specific input/state that caused it.
- The change you made to handle it correctly.

3) **Engineering Decision Entry (up to 2 allowed)**
- A design decision you made.
- An alternative approach you considered.
- Why you chose one approach over another (tradeoffs).

---

### Entry 1
**Date:** 2026-02-24  
**Entry Type:** Engineering Decision  
**Task worked on:** CS210 style alignment (const refs + nullptr + const methods).  
**Issue or decision:**  I needed to decide how to pass objects into list functions and how to handle pointers consistently.  
**Error message / symptom (if applicable):**  N/A  
**What I tried:**  I initially used pass-by-value for `addSpace(T value)` and `addMany(vector<T> values)` because it was simpler to write.  
**Fix / resolution (or final decision):**  I updated signatures to use `const T&` and `const vector<T>&` to avoid copies and match modern C++ conventions. I also standardized pointer checks and initialization using `nullptr`, and marked `print()` / `isEqual()` methods `const` where appropriate.  
**Commit(s):**  `initialize repo, starter files, and apply style conventions`

---

### Entry 2
**Date:** 2026-02-27  
**Entry Type:** Bug Fix  
**Task worked on:**   `addSpace` circular integrity  
**Issue or decision:**  After inserting nodes, traversal did not loop correctly and sometimes printing only showed part of the list.  
**Error message / symptom (if applicable):**  Printing was inconsistent; the list did not behave like a ring.  
**What I tried:**  I printed `headNode`, `tailNode`, and `tailNode-->nextNode` information after each insertion and verified the links.  
**Fix / resolution (or final decision):** I realized I must always maintain `tailNode-->nextNode == headNode`. The fix was to set `tailNode-->nextNode = headNode` after updating the tail in both the empty-list non-empty cases.  
**Commit(s):** `implement addSpace with MAX_SPACES enforcement and circular linking`  

---

### Entry 3
**Date:** 2026-03-02  
**Entry Type:** Edge Case / Testing Entry
**Task worked on:**  `addSpace` circular integrity.  
**Issue or decision:**  Adding more than  40 spaces could potentially corrupt the list if insertions continue after reaching capacity.  
**Error message / symptom (if applicable):**  When testing large inputs (45 spaces), I saw unexpected behavior and incorrect counts.  
**What I tried:**  I generated 45 spaces and used `printBoardOnce()` to validate that the traversal was still correct. 
**Fix / resolution (or final decision):**  I ensured `addMany` stops immediately when `addSpace` returns false, and returns exactly how many were added. This guarantees it stops at 40 and does not corrupt pointers.
**Commit(s):** `implement addMany stopping exactly at capacity`

---

### Entry 4
**Date:** 2026-03-04  
**Entry Type:** Bug Fix  
**Task worked on:** `movePlayer` GO tracking correctness  
**Issue or decision:** My GO counter was wrong in some cases because I didn’t define exactly when “passing GO” occurs.  
**Error message / symptom (if applicable):** `passGoCount` sometimes increased when landing near GO or didn’t increase when wrapping.  
**What I tried:** I tested movement on a small board and logged the player’s node each step. I compared results for moves that land on GO vs moves that pass over GO.  
**Fix / resolution (or final decision):** I defined passing GO as crossing from the tail node back to the head node (tail -> head transition). The fix was to increment `passGoCount` when `playerNode == tailNode` before advancing to `playerNode->nextNode`.  
**Commit(s):** `implement movePlayer traversal and pass GO detection`

---

### Entry 5
**Date:** 2026-03-06  
**Entry Type:** Edge Case / Testing Entry  
**Task worked on:** `findByColor(const string& color)` (Advanced Option A)  
**Issue or decision:** I needed to return all property names that match a given color while traversing the circular linked list exactly once. I didn't realize at first that because the list is circular, a normal `while (current != nullptr)` traversal would never terminate. I also needed to safely handle an empty board.  
**Error message / symptom (if applicable):** When trying my first attempt at findByColor implementation, a `nullptr`-based loop would cause an infinite loop on a circular list causing the program to hang while traversing.  
**What I tried:** I tested the function using a board of 40 generated spaces with repeating colors (Red/Blue/Green/Yellow). I verified, calling `findByColor("Red")` returns a non-empty vector, calling `findByColor("Purple")` returns an empty vector, and calling it on an empty board returns an empty vector without crashing.    
**Fix / resolution (or final decision):** I implemented traversal using a correct circular stop condition (`do { ... } while (current != headNode)`), starting at `headNode` and stopping as soon as the traversal returns to the head. This makes sure exactly one ring traversal occurs, and prevents infinite loops. I also added an early return for `headNode == nullptr`.  
**Commit(s):** `implement findByColor with single-cycle traversal`

---

### Entry 6
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**  
