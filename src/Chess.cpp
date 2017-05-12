/*
*  Author: Alexander Zhu
*  Date Created: November 20, 2016
*  Description: Driver class for Chess game
*  Version: 1.8
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

#include "Board.h"

#include "Utility.h"

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

using namespace std;

// Print Functions
void print_intro();
void print_instructions();

// Parse Functions
void parse_move(const string &input, Tile &old_pos, Tile &new_pos);
int parse_col_label(char col_label);

// Logging Functions
void log_move(ofstream &ofs, Tile old_pos, Tile new_pos, Player player, 
    bool valid_move);

int main(int argc, char *argv[]) {
    regex move_format{ "[a-h][1-8] [a-h][1-8]" };  // Example: a2 a3
    ofstream out_file;
    string log_name;
    bool write_log = false;
    if (argc == 2) {
        log_name = argv[1];
        out_file.open(log_name);
        if (!out_file.is_open()) {
            cerr << "Invalid log name: " << log_name << ".\nExiting now.\n";
            return 1;
        }
        write_log = true;
        cout << "Writing game log to " << log_name << '\n';
        out_file << "n\n";  // Skip instructions on replay
    }

    print_intro();

    while (true) {
        cout << Board::get_instance();
        Tile old_pos, new_pos;
        bool valid_move = false;
        while (!valid_move) {
            Player current_player = Board::get_instance().get_turn();
            cout << "Player " << current_player << "\'s turn. ";
            cout << "Enter your move: ";
            string input;
            if (getline(cin, input)) {
                if (input.substr(0, 4) == "quit") {
                    if (write_log) {
                        assert(out_file.is_open());
                        out_file << "quit\n\nEnd State:\n" << Board::get_instance();
                        out_file.close();
                        cout << "Game log has been saved to: " << log_name << '\n';
                    }
                    cout << "Thanks for playing!\n";
                    return 0;
                }
                else if (input.substr(0, 4) == "help")
                    print_instructions();
                else if (regex_match(input.substr(0, 5), move_format)) {
                    parse_move(input, old_pos, new_pos);
                    try {
                        Board::get_instance().move(old_pos, new_pos);
                        valid_move = true;
                    }
                    catch (Error &e) {
                        cout << e.what() << '\n';
                    }
                    catch (exception &e) {
                        cout << e.what() << '\n';
                        return 1;
                    }
                    catch (...) {
                        cout << "Unknown exception!\n";
                        return 1;
                    }
                    if (write_log)
                        log_move(out_file, old_pos, new_pos, current_player, 
                            valid_move);
                }
                else
                    cerr << "Invalid input -- try again. Enter \"help\" for instructions.\n";
            }  // if
        }  // while
        cout << '\n';
    }  // while
    return 0;
}

/*
Print functions
*/

void print_intro() {
    cout << "Hello! Welcome to chess.\n";
    cout << "Would you like to see the instructions? (y/n): ";
    char option = 0;
    if (cin >> option && option == 'y')
        print_instructions();
    // Ignore any extra input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.clear();
    cout << "Let's get started!\n\n";
}

void print_instructions() {
    cout << " --------------------------------\n";
    cout << "| Rules are standard chess rules.|\n";
    cout << "| Usage:                         |\n";
    cout << "|   Move: [a-h][1-8] [a-h][1-8]  |\n";
    cout << "|   Show Instructions: help      |\n";
    cout << "|   Quit: quit                   |\n";
    cout << " --------------------------------\n";
}

/*
Parse functions
*/

// REQUIRES input is of format: [a-h][1-8] [a-h][1-8]
void parse_move(const string &input, Tile &old_pos, Tile &new_pos) {
    // Read in rows and correct to zero-indexed
    old_pos.row = input[1] - '0' - 1;
    new_pos.row = input[4] - '0' - 1;
    old_pos.col = parse_col_label(input[0]);
    new_pos.col = parse_col_label(input[3]);
}

// REQUIRES col_label is [a-h]
// EFFECTS  Return respective column number
//          Throws exception if col_label is a valid label
int parse_col_label(char col_label) {
    static const unordered_map<char, int> col_labels{
        { 'a', 0 },
        { 'b', 1 },
        { 'c', 2 },
        { 'd', 3 },
        { 'e', 4 },
        { 'f', 5 },
        { 'g', 6 },
        { 'h', 7 }
    };
    auto itr = col_labels.find(col_label);
    assert(itr != col_labels.end());
    return itr->second;
}

/*
Logging functions
*/

// REQUIRES ofs if open
// MODIFIES ofs
// EFFECTS  Write move to log
void log_move(ofstream &ofs, Tile old_pos, Tile new_pos, Player player, 
    bool valid_move) {
    assert(ofs.is_open());
    ofs << old_pos << " " << new_pos << "\t// " << player;
    if (!valid_move)
        ofs << " Invalid move";
    ofs << '\n';
}