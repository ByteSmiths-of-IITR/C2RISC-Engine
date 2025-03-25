
# 📄 Symbol Table Test Suite

## 🚀  Overview
This test suite validates the **design and correctness** of a **scope-aware Symbol Table** implementation. It tests:

- ✔️ Symbol Insertion & Lookup
- ✔️ Scoping & Shadowing
- ✔️ Redeclaration Prevention
- ✔️ User-Defined Types Handling
- ✔️ Scope-based Cleanup
- ✔️ Multi-type support (Variable, Function, Enum, Struct)

---

The main driver file `symTest.cpp` is designed to load **test cases** from `SymTab_TestCases/` and validate the behavior.

---

## 📂 Directory Structure
```
/YourProjectRoot/
│
├── sym.h               // Symbol table header
├── sym.cpp             // Symbol table implementation
├── symTest.cpp         // General test driver (dynamic test loading)
├── stderr.log          // Auto-generated error logs
├── symbol.txt          // Symbol table state dump per test
│
└── SymTab_TestCases/
     ├── tc1.txt        // Test Case 1: Basic Insertion & Lookup
     ├── tc2.txt        // Test Case 2: Shadowing & Type Shadowing
     ├── tc3.txt        // Test Case 3: Multiple Symbol Types
     ├── tc4.txt        // Test Case 4: Redeclaration Error
     ├── tc5.txt        // Test Case 5: Scope Cleanup
     ├── tc6.txt        // Test Case 6: Deep Nested Scopes
     ├── tc7.txt        // Test Case 7: User-Defined Types
```

---

## 📌 How to Use the Test Suite

### 🧠 Running a Test Case

**Note:** `symTest.cpp` is structured to allow inserting any test case **inside `main()` after line 36**.

For each test case:
1. Copy contents of `SymTab_TestCases/tcX.txt`
2. Paste it **below Line 36** (inside the block marked: `// -------------------- Enter your test case below -------------------`)
3. Compile and run:
```bash
make sym
```
4. Check:
   - `symbol.txt` → Symbol table dump
   - `stderr.log` → Errors, if any
   - Console output → Expected behavior

---

## ✅ Test Case Purpose Summary
| Test Case | Description |
|---------- |------------ |
| **tc1.txt** | ✅ Basic Insertion and Lookup |
| **tc2.txt** | ✅ Shadowing and Type Shadowing |
| **tc3.txt** | ✅ Handling Multiple Symbol Types (Variable, Function, Enum) |
| **tc4.txt** | ✅ Redeclaration Error Detection |
| **tc5.txt** | ✅ Scope Cleanup after Exit |
| **tc6.txt** | ✅ Deep Nested Scopes, Shadow Restoration |
| **tc7.txt** | ✅ User-Defined Type Handling (Struct, Union, Enum) |

---

Each test case block **includes the expected output as comments** for comparison.

---

## 📎 Logging & Debugging
- `stderr.log` → Captures runtime errors and signal handler outputs
- `symbol.txt` → Visual dump of the symbol table state after operations
- `std::cerr` lines (with LINE macro) help in debugging and execution tracing.

---

## ⚠ Important Notes
- Always insert test case content **after line 36 in `symTest.cpp`** as per the provided template.
- Use the signal handler for catching runtime errors like segmentation faults.
- Clear `symbol.txt` and `stderr.log` between runs for fresh logs.

---
