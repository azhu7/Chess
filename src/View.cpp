/**
    Author: Alexander Zhu
    Date Created: May 12, 2016
    Description: Implementation for Chess View
*/

#include "View.h"

#include "Board.h"

#include <iostream>
#include <vector>
//*** #include <windows.h>

using std::ostream;
using std::string;
using std::vector;

void View::draw(ostream &ofs) const {
    //*** Colored output...but how to include windows.h in Makefile?
    /*** HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    bool console_error = !GetConsoleScreenBufferInfo(hStdout, &csbi);
    assert(!console_error);
    WORD old_attributes = csbi.wAttributes;
    if (p.get_player() == BLACK)
        SetConsoleTextAttribute(hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
    ofs << p.get_type();
    SetConsoleTextAttribute(hStdout, old_attributes);*/


    // Initialize and populate 2D board
    vector<vector<string>> display(Board::kNum_rows, 
        vector<string>(Board::kNum_cols, "  "));
    for (const auto &pair : piece_positions)
        display[pair.first.row][pair.first.col] = pair.second;

    // Upper key
    ofs << "    a    b    c    d    e    f    g    h\n";
    ofs << "  +----+----+----+----+----+----+----+----+\n";

    // Print rows from bottom up
    for (int row = Board::kNum_rows - 1; row >= 0; --row) {
        ofs << row + 1 << " | ";  // LHS key
        for (int col = 0; col < Board::kNum_cols; ++col) {
            ofs << display[row][col] << " | ";
        }
        ofs << row + 1 << '\n';  // RHS key
        ofs << "  +----+----+----+----+----+----+----+----+\n";  // Row divider
    }

    // Lower key
    ofs << "    a    b    c    d    e    f    g    h\n";
}