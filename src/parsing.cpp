/**
 * parsing.cpp
 * railway-asm
 * 
 * Created on November 29th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#include <vector>
#include <map>
#include <string>

#include "../include/parsing.h"
#include "../include/errors.h"

using namespace std;

map<string, vector<string>> parse_directives(string filename, vector<string> &contents) {
    // Takes the program and splits it up into its directives.
    map<string, vector<string>> directives;
    
    // Loop through the lines and determine if it is the start or end of a directive
    bool directive_active = false;
    string active_directive_name = "";

    for (size_t i = 0; i < contents.size(); i++) {

        // if it is an open parentheses, we can determine that a directive is open.
        // if it detects another open parentheses, we can determine a syntax error.
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