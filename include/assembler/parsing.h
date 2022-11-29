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

vector<string> load_program(string &filepath);
map<string, vector<string>> parse_directive(string filename, vector<string> &contents);
vector<string> text_directive_to_program_memory(vector<string> &program);
vector<string> data_directive_to_memory(vector<string> &data);

#endif