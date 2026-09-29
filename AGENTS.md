# AGENTS.md

## Project Overview
- This is a small C++20 program for solving a Sudoku-like mass puzzle with backtracking.
- The puzzle grid and starting restrictions currently live in `src/Main.cpp`.
- `include/Block.h` defines the cell state: the current value, candidate count, and possible values.

## Build
- Use the existing CMake setup.
- The CMake file is named `cmakelists.txt` in this project.
- Build from the existing build directory when possible:

```sh
cmake --build build
```

## Coding Rules
- Keep changes lightweight and closely scoped to the requested behavior.
- Use two space indentation.
- Use C++20-compatible code.
- Prefer the existing `std::array`-based grid representation unless a requested change requires a different structure.
- Keep puzzle constants, coordinates, and restricted-area rules readable; avoid hiding them behind unnecessary abstractions.
- Do not rewrite the solver style or rename files unless explicitly requested.

## Verification
- After solver changes, build the project with `cmake --build build`.
- If behavior changes, run the generated executable from the build directory and confirm the solution count/output still matches the requested puzzle behavior.
