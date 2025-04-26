# # 8 Queens Problem Solver with SFML visualization

## Description

This is a solution to the classic problem of arranging 8 queens on a chessboard in which no queen attacks the other. 
The project includes:
- Efficient algorithm for finding all possible solutions (92 solutions)
- Filtering of unique solutions (12 fundamental solutions)
- Visualization using the SFML library
- Interactive viewing of solutions
- Saving and uploading solutions

## Implementation features

- C++20 standart with a clean architecture
- Separation of decision logic, storage and display
- Support for board rotations and reflections
- Statistical analysis of queens' positions
- High-quality visualization with fallback mode

## Requirements

- Compiler with C++20 support (GC 10+, Clang 10+, MSVC 19.28+)
- SFML library (version 2.5+)
- CMake (version 3.12+) for assembly

## Installation and assembly

### Linux (Ubuntu/Debian/Fedora)

- for Ubuntu/Debian:
```bash
apt install libsfml-dev cmake g++ 
git clone https://github.com/your-repo/8-queens-sfml.git
cd 8-queens-sfml
mkdir build && cd build
cmake ..
make
```

- for Fedora: 
```bash
dnf install SFML-devel cmake g++ 
...
```

## Gratitude

- The SFML team for the excellent library
- The C++ community for inspiration
