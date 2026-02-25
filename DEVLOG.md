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
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**

---

### Entry 3
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**

---

### Entry 4
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**

---

### Entry 5
**Date:** YYYY-MM-DD  
**Entry Type:** Bug Fix / Edge Case / Engineering Decision  
**Task worked on:**  
**Issue or decision:**  
**Error message / symptom (if applicable):**  
**What I tried:**  
**Fix / resolution (or final decision):**  
**Commit(s):**

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
