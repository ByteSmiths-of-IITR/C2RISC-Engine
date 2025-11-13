# C2RISC-Engine

This GitHub Repo is about our semester long project under the course CSN-352 *Compiler Design* 


## Compiler Specification
Source Language - `C` <br>
Target Machine/Arch - "RISC-V" <br>
Intermediate Representation - "Three Address Code" <br>
Implementation Language - `C++` <br>


# Features in our C2RISC-Engine 
## Basic Features
- Implement arithmetic and logical operators
- Implement `if-else`
- Implement `for` loop
- Implement `while` loop
- Implement `do-while` loop
- Implement `switch` cases
- Implement `int` and `char` arrays
- Work with pointers
- Create and use `struct`
- Use `printf` and `scanf` | A custom version since we are not able to link the standard library
- Implement function calls with arguments
- Use `goto`, `break`, and `continue`
- Use the `static` keyword

## Advanced Features
- Implement recursive function calls
- Use `typedef`
- Implement an `until` loop
- Implement multi-dimensional arrays
- Work with multi-level pointers

## Extra Features
- Extended to all type of arrays
- Any Combination of array, pointer, function levels
- `const` keyword supported

Here's your **usage instruction** converted into a clean and readable **Markdown format**:

---

##  C2RISC-Engine Usage Instructions

#### Usage: `bin/C2RISC_Engine <input_file> [ -o <output_file> ]/[ -t ] [ -d{1,2} <dot_file> ]`

---

### 💡 Compiler Options

| Option               | Description                                                                 |
| -------------------- | --------------------------------------------------------------------------- |
| *(No Arguments)*     | Output will be printed to `stdout` (terminal).                              |
| `-o [<output_file>]` | Send output to a file to `<output_file>` else same name as input create a output with `input_file's base + (.s)` |
| `-t`                 | **Testing Mode** - Appends output to `<input_file>`.                        |

---

### 🐞 Debugging Options

| Option           | Description                                                  |
| ---------------- | ------------------------------------------------------------ |
| `-d1 <dot_file>` | Outputs **Parse Tree** to `<dot_file>`                       |
| `-d2 <dot_file>` | Outputs **Annotated Parse Tree** to `<dot_file>`             |
| `-ir`            | **Stops at the IR (Intermediate Representation) Phase only** |

---




# Major Concepts Used
- Lvalue(Modifiable or Non-Modifiable) & Rvalue
- Backpatching used for control-flow
- Space Change logic for array/pointer derefrencing to accomodate limitations of TAC

- Register allocation (sub-optimal)
- Stack allocation
- Function call
- Function return
- Function arguments

- Live variable analysis
- Dead code elimination
- Constant folding
and more Optimizations
---


> Don't panic for sucide message 👻



