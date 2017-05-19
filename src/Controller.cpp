/**
    Author: Alexander Zhu
    Date Created: May 12, 2017
    Description: Implementation for Chess Controller
*/

#include "Controller.h"

#include "Board.h"
#include "Utility.h"
#include "View.h"

#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_map>

using std::cout; using std::cin;
using std::ofstream;
using std::make_shared;
using std::regex;
using std::unordered_map;
using std::string;
using std::exception;

// Print Functions
void print_intro();
void print_instructions();

// Parse Functions
void parse_move(const string &input, Tile &old_pos, Tile &new_pos);
int parse_col_label(char col_label);

// Logging Functions
void log_move(ofstream &ofs, Tile old_pos, Tile new_pos, Player player,
    bool valid_move);

// Ctor creates and attaches default view.
Controller::Controller()
    : view{ std::make_shared<View>() } {
    Board::get_instance().attach(view);
}

// Dtor closes ofs if it is open.
Controller::~Controller() {
    if (ofs.is_open())
        ofs.close();
}

// Lets user specify an initial board layout.
void Controller::load_board(const string &board_name) const {
    Board::get_instance().load_board(board_name);
}

// Lets user enable logging.
void Controller::enable_logging(const string &log_name) {
    ofs.open(log_name);
    if (!ofs.is_open())
        throw Error{ "Invalid log name!" };
    cout << "Writing game log to " << log_name << '\n';
    ofs << "n\n";  // Skip instructions on replay
}

void Controller::run() {
    regex move_format{ "[a-h][1-8] [a-h][1-8]" };  // Example: a2 a3
    print_intro();
    while (true) {
        view->draw();
        Tile old_pos, new_pos;
        bool valid_move = false;
        while (!valid_move) {
            Player current_player = Board::get_instance().get_turn();
            cout << "Player " << current_player << "\'s turn. ";
            cout << "Enter your move: ";
            string input;
            if (getline(cin, input)) {
                if (input.substr(0, 4) == "quit") {
                    if (ofs.is_open()) {
                        ofs << "quit\n\nEnd State:\n";
                        view->draw(ofs);
                        ofs.close();
                    }
                    cout << "Thanks for playing!\n";
                    return;
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
                        return;
                    }
                    catch (...) {
                        cout << "Unknown exception!\n";
                        return;
                    }
                    if (ofs.is_open())
                        log_move(ofs, old_pos, new_pos, current_player,
                            valid_move);
                }
                else
                    cout << "Invalid input -- try again. Enter \"help\" for instructions.\n";
            }  // if
        }  // while
        cout << '\n';
    }
}

/*
Print functions
*/

// Print introduction and ask user if they want to see the instructions.
void print_intro() {
    cout << "Hello! Welcome to chess.\n";
    cout << "Would you like to see the instructions? (y/n): ";
    char option = 0;
    if (cin >> option && option == 'y')
        print_instructions();
    skip_line();
    cout << "Let's get started!\n\n";
}

// Print instructions to console.
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

// Requires input is of format: [a-h][1-8] [a-h][1-8].
void parse_move(const string &input, Tile &old_pos, Tile &new_pos) {
    // Read in rows and correct to zero-indexed
    old_pos.row = input[1] - '0' - 1;
    new_pos.row = input[4] - '0' - 1;
    old_pos.col = parse_col_label(input[0]);
    new_pos.col = parse_col_label(input[3]);
}

// Return respective column number. Requires col_label is [a-h].
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

// Write move to log. Requires ofs is open.
void log_move(ofstream &ofs, Tile old_pos, Tile new_pos, Player player,
    bool valid_move) {
    assert(ofs.is_open());
    ofs << old_pos << " " << new_pos << "\t// " << player;
    if (!valid_move)
        ofs << " Invalid move";
    ofs << '\n';
}