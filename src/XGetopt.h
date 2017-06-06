// XGetopt.h  Version 1.2
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// This software is released into the public domain.
// You are free to use it in any way you like.
//
// This software is provided "as is" with no expressed
// or implied warranty.  I accept no liability for any
// damage or loss of business that this software may cause.
//
///////////////////////////////////////////////////////////////////////////////

/**
    Author: Alexander Zhu
    Date Created: May 13, 2017
    Description: XGetopt modified for C++
*/

#ifndef XGETOPT_H
#define XGETOPT_H

#include <string>

int optind;
char *optarg;

// Parse command line options.
int getopt(int argc, char *argv[], const std::string &optstring) {
    static char *next = nullptr;
    if (optind == 0)
        next = nullptr;

    optarg = nullptr;

    if (next == nullptr || *next == '\0') {
        if (optind == 0)
            optind++;

        if (optind >= argc || argv[optind][0] != '-' || argv[optind][1] == '\0') {
            optarg = nullptr;
            if (optind < argc)
                optarg = argv[optind];
            return std::char_traits<char>::eof();
        }

        next = argv[optind];
        next++;  // skip past '-'
        optind++;
    }

    char c = *next++;
    size_t cp = optstring.find_first_of(c);

    if (cp == std::string::npos)
        return '?';  // Unspecified option

    cp++;
    if (optstring[cp] == ':') {
        // Find the required parameter
        if (*next != '\0') {
            optarg = next;
            next = nullptr;
        }
        else if (optind < argc) {
            optarg = argv[optind];
            optind++;
        }
        else
            return '?';  // Left out required parameter
    }

    return c;
}

#endif  // !XGETOPT_H