// **********************************************
// Filename:   Sudoku.cpp
// Author:     Daniel Guenther (565154853)
// Date:       January 2015
// Purpose:    Tests and allows access to the Sudoku object
// ************************************************

#include "Sudoku.h"
#include <iostream>
using namespace std;

int main()
{
   cout << "Welcome to the Sudoku Solver!" << endl;
   Sudoku P;
   P.input();
   P.printUnsolved();
   if (P.isValid()) {
      cout << "this is a valid sudoku puzzle" << endl;
   } else {
      cout << "this is an invalid sudoku puzzle" << endl;
   }
   cout << "Solving:" << endl;
   P.solve();
   P.printSolved();
}
