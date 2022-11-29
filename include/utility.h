/**
 * utility.h
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <string>
#include <vector>

using namespace std;

vector<string> load_program(string &filepath);
vector<string> tokenize(string tokenizable, char delim);
int fast_atoi(const char* str);

#endif