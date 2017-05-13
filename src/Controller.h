#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <fstream>
#include <string>

class View;

class Controller {
public:
    // Ctor creates and attaches default view.
    Controller();

    // Dtor closes ofs if it is open.
    ~Controller();

    // Lets user specify an initial board layout.
    void load_board(const std::string &board_name) const;

    // Lets user enable logging.
    void enable_logging(const std::string &log_name);

    // Run the program by accepting user commands.
    void run();

private:
    std::shared_ptr<View> view;
    std::ofstream ofs;  // Set if user wants to log game
};

#endif // !CONTROLLER_H
