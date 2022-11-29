/**
 * main.cpp
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/


#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "../include/errors.h"
#include "../include/assembler/assembler.h"
#include "../include/parsing.h"
#include "../include/utility.h"
#include "../include/linker/stitcher.h"

using namespace std;

/*
railway-asm is a linker & assembler built in to one program. 
*/

int main(int argc, char** argv) {
    if (argc >= 2) {
        
        // BEGIN Linker
        string main = (string) argv[1];
        vector<string> filenames;

        if (argc >= 3) {
            for (int i = 1; i < argc; i++) {
                // check if it is an option, else assume file
                if (((string) argv[i]).at(0) == '-') {
                    // TODO: Option parsing
                } else {
                    filenames.push_back((string) argv[i]);
                }
            }
        }

        // TODO: Combine directives into one. (Potentially. Maybe just one program at a time but this could be an opurtunity for extra credit.)

        // END Linker

        // BEGIN Assembler

        // TODO: Implement assembler using methods defined in instructions.h and parsing.h.

        // END Assembler

    } else {
        cout << "Usage: " << argv[0] << " <main .track filepath> [secondary .track filepath(s)] [...args]" << endl;
    }

    return 0;
}