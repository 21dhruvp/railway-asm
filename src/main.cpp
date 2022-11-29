/**
 * main.cpp
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

// standard library headers
#include <iostream>
#include <string>
#include <vector>
#include <map>


// custom headers
#include "../include/errors.h"
#include "../include/parsing.h"
#include "../include/utility.h"

#include "../include/assembler/instructions.h"
#include "../include/assembler/assembler.h"

#include "../include/linker/stitcher.h"
#include "../include/linker/validator.h"

using namespace std;

/*
railway-asm is a linker & assembler built in to one program. 
*/

int main(int argc, char** argv) {
    if (argc >= 2) {

        string main = (string) argv[1];
        vector<string> filenames;

        if (argc >= 3) {
            for (int i = 2; i < argc; i++) {
                // check if it is an option, else assume file
                if (((string) argv[i]).at(0) == '-') {
                    // TODO: Option parsing
                } else {
                    filenames.push_back((string) argv[i]);
                }
            }
        }

        vector<string> main_contents = load_program(main);
        map<string, vector<string>> main_directives = parse_directives(main_contents);

        stitch(main_directives, filenames);

        // TODO: Validate syntax of files before assembling.
        //!Defined but not implemented!
        validate(main_directives);

        // TODO: Implement assembler using methods defined in instructions.h and parsing.h.

    } else {
        cout << "Usage: " << argv[0] << " <main .track filepath> [secondary .track filepath(s)] [...args]" << endl;
    }

    return 0;
}