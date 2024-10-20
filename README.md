<h1 align="center">
  <br>
  <img src="./sudoku.gif" 
  width="400">
  <br>
  Sudoku Solver
  <br>
</h1>

<h5 align="center">A Sudoku solver, developped in C++ and compatible with Linux and Windows, displayed in CLI</h5>

# Concepts applied in this project
* CMake
* Backtracking algorithm
* Cross-platform compatibility and compilation
* Object-oriented programming in C++

# Usage
```bash
./SudokuSolver
```
(which reads automatically the `./test.txt` file)
or 
```bash
./SudokuSolver path-of-file
```

# Compilation
## Linux
To get the `Makefile`, run: 
```bash
cmake .
```
(or `cmake path_to_the_folder` to compile from another folder)

Then:
```bash
make
```

will build the executable `SudokuSolver`.

## Windows
The easiest way to compile it is creating a Visual Studio project, with cmake :
```bash
cmake .
```
Open the `.sln` project file created after this command, and run the executable using Visual Studio.
