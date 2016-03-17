SudokuSolver: main.o Sudoku.o
	g++ -o SudokuSolver main.o Sudoku.o

main.o: main.cpp Sudoku.h
	g++ -c main.cpp

Sudoku.o: Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp

clean:
	rm *.o SudokuSolver

debug: main.cpp Sudoku.cpp Sudoku.h
	g++ -g -o SudokuSolver main.cpp Sudoku.cpp
