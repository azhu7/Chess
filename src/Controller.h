#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>
#include <fstream>

class View;

class Controller {
public:
    // Ctor
    Controller();

    // Run the program by accepting user commands.
    void run();

    // Lets user enable logging.
    void enable_logging(std::ofstream &ofs_) { ofs = std::move(ofs_); }

private:
    std::shared_ptr<View> view;
    std::ofstream ofs;  // Set if user wants to log game
};

#endif // !CONTROLLER_H
