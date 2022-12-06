/**
 * main.cpp
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "../../include/linker/stitcher.h"
#include "../../include/parsing.h"
#include "../../include/utility.h"

using namespace std;

void stitch(map<string, vector<string>> &main, vector<string> secondary_filepaths) {
    vector<string> stitched;

    for (const auto &directives : main) {
        string key = directives.first;

        for (size_t i = 0; i < main[key].size(); i++) {
            if (main[key][i].size() == 0) {
                continue;
            }

            main[key][i] = reduce(main[key][i]);

            // look for outside insertions
            if (main[key][i].at(0) == '%') {
                string check_file = main[key][i].substr(1, main[key][i].size() - 1);
                string filepath = "";

                // find matching file for the outsize reference
                for (size_t j = 0; j < secondary_filepaths.size(); j++) {
                    // check for reference string in filepath string
                    if (secondary_filepaths[j].find(check_file) != string::npos) {
                        filepath = secondary_filepaths[j];
                        break;
                    }
                }

                // get insertable contents
                vector<string> stitchable = get_directive_from_file(filepath, key);

                // remove reference
                main[key].erase(main[key].begin() + i);

                // insert all contents at the position of the reference
                for (size_t j = 0; j < stitchable.size(); j++) {
                    stitchable[j] = reduce(stitchable[j]);
                    main[key].insert(main[key].begin() + i, stitchable[j]);
                }
            }
        }

        
    }
}

vector<string> get_directive_from_file(string filepath, string directive_name) {

    vector<string> program_contents = load_program(filepath);
    map<string, vector<string>> program_directives = parse_directives(program_contents);

    return program_directives[directive_name];
}