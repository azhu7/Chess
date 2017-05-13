/**
    Author: Alexander Zhu
    Date Created: November 20, 2016
    Description: Driver class for Chess game

    ***TODO:
        Promotions!!
        Verbose output detailing move outcomes
        Save feature? Write moves to log for future replay. Fix for promotions.
        How to check for correct test output state? Read in board state and check for equality? (overload == for board AND piece)
        Stats feature. type stats to see some stats like #moves, pieces captured
        Detect check, checkmate, get out of check, stalemate (may need hash for pieces)
*/

#include "Controller.h"

#include "XGetopt.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    Controller controller;

    // Configure controller
    try {
        string board_file = "default_board.txt";

        int c;
        while ((c = getopt(argc, argv, "b:L:")) != char_traits<char>::eof()) {
            switch (c) {
            case 'b': {
                // User specified board file
                board_file = optarg;
                break;
            }
            case 'L': {
                // User requested logging
                controller.enable_logging(optarg);
                break;
            }
            case '?': {
                cout << "Error: illegal option " << argv[optind - 1] << '\n';
                cout << "Usage: ./bin/chess [-b board_name] [-L log_name]";
                return 1;
            }
            default: {
                cout << "Error: no handler for option " << (char)c << '\n';
                cout << "Usage: ./bin/chess [-b board_name] [-L log_name]";
                return 1;
            }
            }  // switch
        }  // while

        controller.load_board(board_file);
    }
    catch (exception &e) {
        cout << e.what() << '\n';
        return 1;
    }
    catch (...) {
        cout << "Unknown exception!\n";
        return 1;
    }

    controller.run();
    return 0;
}