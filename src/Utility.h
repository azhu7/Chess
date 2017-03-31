/**
    Author: Alexander Zhu
    Date Created: March 31, 2017
    Description: Header file for Chess Utility
*/

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