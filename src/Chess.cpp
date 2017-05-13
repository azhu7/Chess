/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Driver class for Chess game
*
*  ***TODO:
*    Promotions!!
*    Verbose output detailing move outcomes
*    Save feature? Write moves to log for future replay. Fix for promotions.
*    How to check for correct test output state? Read in board state and check for equality? (overload == for board AND piece)
*    Stats feature. type stats to see some stats like #moves, pieces captured
*    Detect check, checkmate, get out of check, stalemate (may need hash for pieces)
*    Clean up loops: 1-liners, definition conditions
*    Change privates to no _ and ctor inputs to _
*    File for board layout, have board read it in?
*/

#include "Controller.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    Controller controller;
    if (argc == 2) {
        string log_name = argv[1];
        ofstream out_file{ log_name };
        if (!out_file.is_open()) {
            cerr << "Invalid log name: " << log_name << ".\nExiting now.\n";
            return 1;
        }
        cout << "Writing game log to " << log_name << '\n';
        out_file << "n\n";  // Skip instructions on replay
        controller.enable_logging(out_file);
    }
    controller.run();
    return 0;
}