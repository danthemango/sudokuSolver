SudokuSolver: obj/main.o obj/Sudoku.o
	g++ -o SudokuSolver obj/main.o obj/Sudoku.o

obj/main.o: src/main.cpp src/Sudoku.h
	g++ -c src/main.cpp -o obj/main.o

obj/Sudoku.o: src/Sudoku.cpp src/Sudoku.h
	g++ -c src/Sudoku.cpp -o obj/Sudoku.o

clean:
	rm obj/* SudokuSolver

debug: src/main.cpp src/Sudoku.cpp src/Sudoku.h
	g++ -g -o SudokuSolver src/main.cpp src/Sudoku.cpp
