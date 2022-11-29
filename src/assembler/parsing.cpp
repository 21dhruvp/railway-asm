/**
 * parsing.cpp
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>

#include "../../include/assembler/parsing.h"
#include "../../include/errors.h"

using namespace std;

vector<string> load_program(string &filepath) {
    // Takes a filepath and loads it line by line into a list of instructions. Not parsed into directives.
    vector<string> lines;

    string line;
    ifstream file(filepath);

    // iterates through every line in the program
    while (file.is_open()) {
        if (getline(file, line)) {
            lines.push_back(line);
        }
    }

    return lines;
}

map<string, vector<string>> parse_directives(string filename, vector<string> &contents) {
    // Takes the program and splits it up into its directives.
    map<string, vector<string>> directives;
    
    // Loop through the lines and determine if it is the start or end of a directive
    bool directive_active = false;
    string active_directive_name = "";

    for (size_t i = 0; i < contents.size(); i++) {

        // if it is an open parentheses, we can determine that a directive is open.
        // if it detects 2 open parentheses, we can determine a syntax error.
        if (contents[i].at(0) == '(') {

            if (directive_active) {
                string message = Color().RED+"error on line #"+to_string(i)+" in file '"+filename+"'"+Color().reset+": Cannot open another directive while a directive is already open!";
                throw railway_syntax_error(&message[0]);
            }

            directive_active = true;
            active_directive_name = contents[i].replace(0, 1, "");
            continue;
        }

        if (contents[i].at(contents[i].length() - 1) == ')') {
            directive_active = false;
            active_directive_name = "";
            continue;
        }

        if (directive_active) {
            directives[active_directive_name].push_back(contents[i]);
        }
    }

    return directives;
}

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