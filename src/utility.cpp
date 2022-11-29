/**
 * utility.cpp
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#include <string>
#include <vector>

#include "../include/utility.h"

using namespace std;

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