// **********************************************
// Filename:   Sudoku.cpp
// Author:     Daniel Guenther (565154853)
// Date:       January 2015
// Purpose:    Implements the Sudoku object
// ************************************************

#ifndef SUDOKU_H

#include <string>
using namespace std;
// the default size of the square in the grid
// ex. defaultsize of 3 means we have a 3^2 board 
const int DEFAULTSIZE = 3;
// character for unsolved chars in input
const char DEFAULTCHAR = ' ';
// character indicating unsolved char for printing
const char UNSOLVEDCHAR = '-';
// an invalid char to declare the end of input
const char INVALID = '0';
// the full list of symbols to be used in the puzzle
const string SYMBOLS = "123456789";

class Sudoku{
   public:
      Sudoku(); // constructor for empty grid
      Sudoku(string newGrid); // constructor with string input
      Sudoku(const Sudoku& input); // copy constructor
      ~Sudoku(); // destructor
      //prompt the user for an unsolved grid
      void input();
      //take a string and put it on the grid
      void input(string newGrid);
      //print the unsolved grid
      void printUnsolved();
      //print the solved grid
      void printSolved();
      // check if the entered grid is a valid sudoku puzzle
      // will return true even if it is solved
      bool isValid();
      // returns true if the puzzle has been solved
      bool isSolved();
      //solve the puzzle, return true if this is the 
      //only possible solution
      bool solve();
   private:
      //print a given string with the Sudoku Syntax
      void print(string puzzle);
      //the unsolved grid
      string unsolvedGrid;
      //the solved grid
      string solvedGrid;
      // dimensions of the puzzle grid
      int width;
      int height;
      int size; // == width * height
      int squareWidth; // the square segments
      int squareHeight;
      // number of squares in each direction
      int hNumSquares;
      int vNumSquares;
      // a solution string
      struct solution{
         int pos;
         string solutions;
      };
      // full list of all possible solutions
      solution* fullList;
      //set the grid values to default values
      void setDefaults();
      //returns true if the symbol at pos is unique in its
      //square, line and column 
      bool isUnique(int pos, const string puzzle);
      //runs isUnique with unsolvedGrid implied string
      bool isUnique(int pos);
      // returns true if the symbol is unique in the square, row and
      // column
      bool isUnique(int pos, char symbol, string puzzle);
      // returns the integer position of the x and y coordinates
      int getPos(int x, int y);
      // get x and y position from integer pos
      void getXY(int& x, int& y, int pos);
      // returns a string with all possible solutions in pos
      string getSolutions(int pos, const string puzzle);
      //returns true if the string is a valid sudoku puzzle
      bool isValid(string puzzle);
      //get the full list of possible solutions for every empty space
      void getSolutionList();
      //get a possible solution for the sudoku puzzle
      Sudoku getPossibleSolution(const Sudoku& input);
};

#endif // SUDOKU_H
