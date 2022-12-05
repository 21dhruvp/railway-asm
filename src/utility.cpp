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

#include "../include/errors.h"
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

vector<string> tokenize(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
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

    transform(t.begin(), t.end(), t.begin(), [](char c){ return tolower(c); });

    s = t;
}

string binary_n_bit_representation(int n, int width) {
    string bin = "";

     while (n != 0) {
        bin += (n % 2 == 0 ? "0" : "1");
        n /= 2;
    };

    if (bin.size() > width) {
        string message = Color().RED+"missed value in validator"+Color().reset+": Integer too large!";
        throw railway_syntax_error(&message[0]);
    } else if (bin.size() < width) {
        int len = bin.size();
        for (int i = 0; i < width - len; i++) {
            bin = "0"+bin;
        }
    }

    return bin;
}