# sudokuSolver
A fairly rudamentary sudoku grid solving application

## Example
```
$ make
g++ -c src/main.cpp -o obj/main.o
g++ -c src/Sudoku.cpp -o obj/Sudoku.o
g++ -o SudokuSolver obj/main.o obj/Sudoku.o

$ ./SudokuSolver < samplePuzzles/unsolved.sudoku
Welcome to the Sudoku Solver!
Please enter a sudoku puzzle:

 - 3 - | - 9 - | 1 7 4
 - 9 6 | - - - | - - -
 4 - - | - 1 - | - - -
-----------------------
 - 2 - | 4 - 6 | - - 8
 - - - | - - - | - - -
 8 - - | 9 - 2 | - 3 -
-----------------------
 - - - | - 2 - | - - 5
 - - - | - - - | 7 9 -
 6 1 5 | - 7 - | - 2 -
this is a valid sudoku puzzle
Solving:

 2 3 8 | 6 9 5 | 1 7 4
 1 9 6 | 7 4 8 | 3 5 2
 4 5 7 | 2 1 3 | 9 8 6
-----------------------
 7 2 9 | 4 3 6 | 5 1 8
 5 6 3 | 1 8 7 | 2 4 9
 8 4 1 | 9 5 2 | 6 3 7
-----------------------
 9 7 4 | 3 2 1 | 8 6 5
 3 8 2 | 5 6 4 | 7 9 1
 6 1 5 | 8 7 9 | 4 2 3
```

## Use
The sudoku puzzle may be typed in the command line but I usually just pipe it in from a file (like the ones in the samplePuzzles folder)

Note that: 

- Spaces (' ') indicate missing numbers in the puzzle
- 0 marks the end of a puzzle, but it will only accept the first 81 numbers anyway
- The program will ensure the entered puzzle does not immediately contradict the rules of Sudoku

However 

- it does not ensure a given puzzle is solvable
- It also does not check for multiple possible solutions, it merely provides the first possible solution it stumbles upon

## Why?
I developed this program shortly after completing the prolog version for a class. I wanted to see what it would look like in C++ instead, and see how much longer it would take to create and analyze the runtime efficiency.

## TODOs
- turn it into an n*n sudoku board solver (with arbitrary symbols)
- check if other possible solutions exist (enumerate them?)
