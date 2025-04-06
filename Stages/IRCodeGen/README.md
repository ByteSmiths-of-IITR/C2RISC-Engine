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
- Use `printf` and `scanf`
- Implement function calls with arguments
- Use `goto`, `break`, and `continue`
- Use the `static` keyword

## Advanced Features
- Implement recursive function calls
- Perform dynamic memory allocation
- Use `typedef`
- Use `enum`, `union`, and `struct`
- Implement an `until` loop
- Implement multi-dimensional arrays
- Work with multi-level pointers
- Use function pointers
- Handle command-line input
- Implement function calls with variable arguments

## Extra Features
- Extended to all type of arrays
- Any Combination of array, pointer, function levels
- `const` keyword supported


# Instructions to `Run`

## Building the Compiler
To build the compiler, execute the following command in the main project directory:
```bash
make compiler
```

## Running Tests
To test the compiler, use the following command:
```bash
bash run.sh <testFolderNumber>
```
This will execute all test cases in the specified test folder.  
For example:
```bash
bash run.sh 3
```
This will run all test cases under the folder `test/3. Declaration`.

## One-on-One Analysis
Follow these steps for analyzing a single `.c` program:

1. Place your `.c` program in the `input/input.c` file.

2. Use the following commands for different purposes:
    - **Build the Compiler**:  
      Run:
      ```bash
      make compiler
      ```
      This will generate an executable file at `bin/C2RISC_Engine`.

    - **Check Input Instructions**:  
      Run:
      ```bash
      ./bin/C2RISC_Engine
      ```

    - **Simplified Debugging**:  
      Run:
      ```bash
      make debugging
      ```
      This will process the `input.c` file and display the results directly.

    - **Detailed Analysis**:  
      After running the above commands, you can analyze the generated parse tree in the file `output/A_Ptree.svg` to understand the processing flow.

# Major Concepts Used
- Lvalue(Modifiable or Non-Modifiable) & Rvalue
- Backpatching used for control-flow
- Space Change logic for array/pointer derefrencing to accomodate limitations of TAC

---


> Don't panic for sucide message 👻