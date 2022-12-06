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

vector<string> strip_comments(vector<string> &contents);
map<string, vector<string>> parse_directives(vector<string> &contents);
vector<string> calculate_data_labels(vector<string> &data_direcrtive);

#endif