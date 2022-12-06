/**
 * main.cpp
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#ifndef STITCHER_H
#define STITCHER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

void stitch(map<string, vector<string>> &main, vector<string> secondary_filepaths);
vector<string> get_directive_from_file(string filepath, string directive_name);

#endif