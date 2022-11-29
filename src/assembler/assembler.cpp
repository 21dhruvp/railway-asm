/**
 * assembler.cpp
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#include <vector>
#include <map>
#include <string>

#include "../../include/assembler/assembler.h"
#include "../../include/errors.h"

using namespace std;

vector<string> text_directive_to_program_memory(vector<string> &program) {
    // TODO: Takes the text directive and converts it into program memory. 16 bit instructions. Maintains program structure but in binary form.
    vector<string> machine_code;

    return machine_code;
}

vector<string> data_directive_to_memory(vector<string> &data) {
    // TODO: Takes the data directive and converts it into bytes compatible with Logisim's memory component.
    vector<string> bytes;

    return bytes;
}