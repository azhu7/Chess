#ifndef UTILITY_H
#define UTILITY_H

#include <exception>
#include <ios>

class Error : public std::exception {
public:
    Error(const char *msg_) : msg{ msg_ } {}
    const char *what() const noexcept override { return msg; }
private:
    const char *msg;
};

#endif  // !UTILITY_H