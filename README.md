# Lisp Interpreter (Toy Project)

This is a toy Lisp interpreter written in C++. It is a work in progress and serves as an educational project to explore concepts like tokenization, parsing, AST (Abstract Syntax Tree) construction, and a recursive runtime execution model.

## Features

- **Tokenization**: Splits user input into meaningful tokens.
- **Parsing**: Builds an AST from the tokenized input.
- **Runtime Execution**: Evaluates expressions recursively from bottom to top.
- **Variables**: Stored in a hashmap for fast lookups.
- **Functions**: Defined and stored as structured data in a hashmap.
- **Basic Arithmetic**: Supports operations like `+`, `*`, etc.

## Example Code Execution

Given the following input:

```lisp
((+ (Func pol (a b) (* (set test 10) test test test b)) (pol 10 10) (pol 10 10) ))
```

- `pol` is a function that takes two parameters (`a` and `b`).
- It defines a local variable `test` and performs multiplication.
- The function is invoked twice with values `(10, 10)`, and the results are summed.

## Project Structure

```
.
├── main.cpp           # Entry point of the interpreter
├── makefile           # Makefile to build the project
├── run.sh             # Script to compile and run the interpreter
├── src/               # Source code directory
│   ├── FuncImpl.cpp   # Function implementation
│   ├── FuncImpl.h     # Function header
│   ├── Runtime.cpp    # Runtime execution logic
│   ├── Runtime.h      # Runtime header
│   ├── Tokenizer.cpp  # Tokenizer implementation
│   ├── Tokenizer.h    # Tokenizer header
│   ├── TreeBuilder.cpp# AST builder implementation
│   ├── TreeBuilder.h  # AST builder header
│   ├── log.hpp        # Logging utilities
└── .vscode/           # VSCode settings
```

## How to Build and Run

Use the provided `run.sh` script:

```sh
./run.sh
```

Alternatively, you can manually build and run:

```sh
make clean  # Clean previous build
make        # Compile the program
./my_program # Run the compiled executable
```

## Dependencies

- C++ Compiler (GCC or Clang recommended)
- Standard C++ Libraries

## Future Improvements

- Expand supported Lisp-like syntax.
- Improve error handling and debugging output.
- Add support for more Lisp features (e.g., conditionals, lists).
- Implement a REPL (Read-Eval-Print Loop) mode.

## License

This project is for educational purposes and does not currently have a specific license. Feel free to explore and modify it as you wish!

---

Feel free to contribute or give feedback on this toy Lisp interpreter!

