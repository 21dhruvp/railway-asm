/**
 * assembler.h
 * railway-asm
 * 
 * Created on November 29th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <vector>
#include <map>
#include <string>

using namespace std;

vector<string> text_directive_to_program_memory(vector<string> &program);
vector<string> data_directive_to_memory(vector<string> &data);

#endif