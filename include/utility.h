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
void write_memory_file(string &filepath, string &contents);
vector<string> tokenize(string s, string delimiter);
int fast_atoi(const char* str);
void trim(string& s);
string binary_n_bit_representation(int n, int width);

#endif