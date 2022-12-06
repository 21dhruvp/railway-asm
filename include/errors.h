/**
 * errors.h
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <string>

using namespace std;

struct Color {
    string RED = "\033[1;31m";
    string BLUE = "\033[1;34m";
    string GREEN = "\033[1;32m";
    string YELLOW = "\033[1;33m";

    string reset = "\033[0m";
};

class railway_syntax_error : public exception {
    private:
        char * message;

    public:
        railway_syntax_error(char* msg) : message(msg) {}
        const char* what() const noexcept override {
            return message;
        }
};

class railway_value_error : public exception{
    private:
        char * message;

    public:
        railway_value_error(char * msg) : message(msg) {}
        const char* what() const noexcept override {
            return message;
        }
};

#endif