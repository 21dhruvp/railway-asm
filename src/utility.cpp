/**
 * utility.cpp
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "../include/utility.h"

using namespace std;

vector<string> load_program(string &filepath) {
    // Takes a filepath and loads it line by line into a list of instructions. Not parsed into directives.
    vector<string> lines;

    string line;
    ifstream file(filepath);

    // iterates through every line in the program
    while (getline(file, line)) {
        lines.push_back(line);
    }

    file.close();

    return lines;
}

vector<string> tokenize(string tokenizable, char delim) {
    vector<string> tokenized;
    string temp;
    
    for (size_t i = 0; i < tokenizable.size(); i++) {
        if (tokenizable.at(i) == delim) {
            tokenized.push_back(temp);
            temp = "";
        } else {
            temp.append(to_string(tokenizable.at(i)));
        }
    }

    return tokenized;
}

int fast_atoi(const char* str) {
    int val = 0;

    while(*str) {
        val = val * 10 + (*str++ - '0');
    }

    return val;
}

void trim(string& s)  {
    string t = "";

    int i = 0;
    while (s[i] == ' ') i++;
    while (s[i] == '\t') i++;
    while (i < s.length()) {
        t += s[i];
        i++;
    }

    s = t;
}