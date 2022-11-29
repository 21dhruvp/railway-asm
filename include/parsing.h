/**
 * parsing.h
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#ifndef PARSING_H
#define PARSING_H

#include <vector>
#include <map>
#include <string>

using namespace std;

map<string, vector<string>> parse_directives(string filename, vector<string> &contents);

#endif