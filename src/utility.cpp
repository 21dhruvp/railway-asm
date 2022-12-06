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
#include <bitset>
#include <algorithm>

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

void write_memory_file(string &filepath, string &contents) {
    ofstream f;

    f.open(filepath);
    f << contents;
    f.close();
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

string trim(string &str, const string &whitespace) {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

string reduce(string &str, const string &fill, const string &whitespace) {
    // trim first
    string result = trim(str, whitespace);

    // replace sub ranges
    size_t begin = result.find_first_of(whitespace);
    while (begin != std::string::npos)
    {
        size_t end = result.find_first_not_of(whitespace, begin);
        size_t range = end - begin;

        result.replace(begin, range, fill);

        size_t n_start = begin + fill.length();
        begin = result.find_first_of(whitespace, n_start);
    }

    transform(result.begin(), result.end(), result.begin(), [](char c){ return tolower(c); });

    return result;
}

string binary_n_bit_representation(int n, int width) {
    string bin = bitset<64>(n).to_string();

    const auto start = bin.find('1');
     
    if(start != string::npos) {
        bin = bin.substr(start);
    }

    if (n == 0) {
        bin = "0";
    }
    
    if (bin.size() > static_cast<size_t>(width)) {
        string message = Color().RED+"missed value in validator"+Color().reset+": Integer too large! ("+(to_string(n))+")";
        throw railway_syntax_error(&message[0]);
    } else if (bin.size() < static_cast<size_t>(width)) {
        int len = bin.size();
        for (int i = 0; i < width - len; i++) {
            bin = "0"+bin;
        }
    }

    return bin;
}