// **********************************************
// Filename:   Sudoku.cpp
// Author:     Daniel Guenther (565154853)
// Date:       January 2015
// Purpose:    Implements the Sudoku object
// ************************************************

#include "Sudoku.h"
#include <iostream>
using namespace std;

Sudoku::Sudoku()
{
   setDefaults();

   //initialize the grid
   for(int i = 0; i < size; i++) {
      unsolvedGrid += DEFAULTCHAR;
   }
}

Sudoku::Sudoku(const Sudoku& input)
{
}

Sudoku::~Sudoku()
{
   if(fullList) {
      delete [] fullList;
   }
}

void Sudoku::setDefaults()
{
   //set the size of the grid
   fullList = NULL;
   squareWidth = DEFAULTSIZE;
   squareHeight = DEFAULTSIZE;
   hNumSquares = DEFAULTSIZE;
   vNumSquares = DEFAULTSIZE;
   width = squareWidth * hNumSquares;
   height = squareHeight * vNumSquares;
   size = width*height;
   
   //initialize the grids
   unsolvedGrid = "";
   solvedGrid = "";
}

Sudoku::Sudoku(string newGrid)
{
   setDefaults();
   input(newGrid);
}

void Sudoku::input(string newGrid)
{
   //the number of chars to copy to the grid
   int toCopy = 0;
   if (newGrid.length() <= size) {
      toCopy = newGrid.length();
   } else if (newGrid.length() > size) {
      toCopy = size;
   }

   //create a new grid with the string
   unsolvedGrid = "";
   for(int i = 0; i < toCopy; i++) {
      unsolvedGrid += newGrid[i];
   }

   //fill in the remainder of the grid
   int remaining = 0;
   if (toCopy < size) {
      remaining = size - toCopy;
   }
   for(int i = 0; i < remaining; i++) {
      unsolvedGrid += DEFAULTCHAR;
   }
}

void Sudoku::input()
{
   // initialize grid
   unsolvedGrid = "";
   
   // get input from user
   cout << "Please enter a sudoku puzzle:" << endl;
   char letter = '\n';
   for (int i = 0; i < size; i++) {
      if (letter != INVALID) {

         // get input (ignoring newline)
         letter = '\n';
         while (letter == '\n') {
            letter = cin.get();
         }

         //put it on the grid
         if (letter != INVALID) {
            if (letter == DEFAULTCHAR) {
            }
            unsolvedGrid += letter;
         } else {
            unsolvedGrid += DEFAULTCHAR;
         }
      } else {
         unsolvedGrid += DEFAULTCHAR;
      }
   }
}

void Sudoku::print(string puzzle)
{
   //print the grid
   for (int row= 0; row< height; row++) {
      cout << endl;
      
      //draw horizontal row
      if ((row != 0) && (row % squareHeight == 0)) {
         for (int col = 0; col < width + hNumSquares - 1; col++) {
            cout << "--";
         }
         cout << '-';
         cout << endl;
      }

      // draw numbers
      for (int col = 0; col < width; col++) {
         cout << ' ';
         // draw vertial column
         if ((col != 0) && (col % squareWidth == 0)) {
            cout << "| ";
         }
         if (puzzle[row * width + col] == DEFAULTCHAR) {
            cout << UNSOLVEDCHAR;
         } else {
            cout << puzzle[row * width + col];
         }
      }
   }
   cout << endl;
}

void Sudoku::printUnsolved()
{
   print(unsolvedGrid);
}

void Sudoku::printSolved()
{
   print(solvedGrid);
}

bool Sudoku::isValid(string puzzle)
{
   //check if any are not unique
   for (int i = 0; i < size; i++) {
      if (!isUnique(i, solvedGrid[i], solvedGrid)) {
         return false;
      }
   }
   
   //declare valid
   return true;
}

bool Sudoku::isValid()
{
   //check if any are not unique
   for (int i = 0; i < size; i++) {
      if (!isUnique(i)) {
         return false;
      }
   }
   
   //declare valid
   return true;
}

bool Sudoku::isUnique(int pos, const string puzzle)
{
   return isUnique(pos, puzzle[pos], puzzle);
}

bool Sudoku::isUnique(int pos)
{
   return isUnique(pos, unsolvedGrid[pos], unsolvedGrid);
}

bool Sudoku::isUnique(int pos, char symbol, const string puzzle)
{
   // ignore spaces
   if (symbol == DEFAULTCHAR) {
      return true;
   }

   //check this line
   int linestart = width * (pos / width);
   int lineend = linestart + width;
   for (int i = linestart; i < lineend; i++) {
      if ((pos != i) && (puzzle[i] == symbol)) {
         return false;
      }
   }

   //check this column
   int x, y;
   getXY(x, y, pos);
   for (int i = 0; i < height; i++) {
      if ((getPos(x,i) != pos) &&
         (puzzle[getPos(x,i)] == symbol)) 
      {
         return false;
      }
   }

   //check the square
   int squareStartX = squareWidth * (x / squareWidth);
   int squareStartY = squareHeight * (y / squareHeight);
   for (int row = squareStartY; row < squareStartY + squareHeight; 
      row++) 
   {
      for (int col = squareStartX; col < squareStartX + squareWidth;
         col++) 
      {
         if ((getPos(col,row) != pos) && 
            (puzzle[getPos(col,row)] == symbol)) 
         {
            return false;
         }
      }
   }

   //declare unique
   return true;
}

int Sudoku::getPos(int x, int y)
{
   return y * width + x;
}

void Sudoku::getXY(int& x, int& y, int pos)
{
   x = pos % width; 
   y = pos / width;
}

bool Sudoku::solve()
{
   //don't try if the problem is invalid
   if (!isValid()) {
      for (int i = 0; i < size; i++) {
         solvedGrid += DEFAULTCHAR;
      }
      return false;
   }
   solvedGrid = unsolvedGrid;

   // get the number of unsolved spaces on the grid
   int unsolved = 0;
   for (int i = 0; i < size; i++) {
      if (solvedGrid[i] == DEFAULTCHAR) {
         unsolved++;
      }
   }

   // find all of the unsolved places, and try the first possible
   // solution
   // get list of all positions with unsolved squares,
   int* unsolvedPos = new int[unsolved];
   // list of all possible solutions in that place
   string* solutionsList = new string[unsolved];
   // number of choices which can be made
   int* numChoices = new int[unsolved];
   // initialize a list of choices already made
   int* choice = new int[unsolved];

   // get list of positions with unsolved square
   int i = 0, pos = 0;
   while (i < size) {
      if (solvedGrid[i] == DEFAULTCHAR) {
         unsolvedPos[pos] = i;
         pos++;
      }
      i++;
   }

   // get a solution to the puzzle
   i = 0;
   while ((i < unsolved) && (i >= 0)) {
      // get the index of this unsolved square
      int pos = unsolvedPos[i];

      solutionsList[i] = getSolutions(pos,solvedGrid);
      numChoices[i] = solutionsList[i].length();

      if (numChoices[i] > choice[i]) {
         // make a choice and see if it works
         solvedGrid[pos] = solutionsList[i][choice[i]];
         i++;
      } else {
         // otherwise reset this pos' choice, go back one square and
         // make the next possible choice for the previous square
         solvedGrid[pos] = DEFAULTCHAR;
         choice[i] = 0;
         i--;
         choice[i]++;
      }
   }

   delete [] unsolvedPos;
   delete [] solutionsList;
   delete [] numChoices;
   delete [] choice;

   if (i < 0) {
      cout << "didn't work" << endl;
      return false;
   }
}

string Sudoku::getSolutions(int pos, const string puzzle)
{
   // get symbols acceptable in pos
   string theSolutions;
   for (int i = 0; i < SYMBOLS.length(); i++) {
      if (isUnique(pos, SYMBOLS[i], puzzle)) {
         theSolutions += SYMBOLS[i];
      }
   }
   return theSolutions;
} 
