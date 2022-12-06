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
        string output_directory = "./";

        if (argc >= 3) {
            for (int i = 2; i < argc; i++) {
                // check if it is an option, else assume file
                if (((string) argv[i]).at(0) == '-') {
                    if ((string) argv[i] == "-o" || (string) argv[i] == "--out") {
                        output_directory = (string) argv[++i];
                    }
                } else {
                    filenames.push_back((string) argv[i]);
                }
            }
        }

        vector<string> main_contents = load_program(main);
        main_contents = strip_comments(main_contents);
        map<string, vector<string>> main_directives = parse_directives(main_contents);

        stitch(main_directives, filenames);

        for (size_t i = 0; i < main_directives["date"].size(); i++) {
            cout << main_directives["data"][i] << endl;
        }

        // Validate syntax of files before assembling.
        validate(main_directives);

        // Implement assembler using methods defined in instructions.h and assembler.h.
        vector<string> data_labels = calculate_data_labels(main_directives["data"]);

        string program_memory = text_directive_to_program_memory(main_directives["program"], data_labels);
        string data_memory = data_directive_to_memory(main_directives["data"]);

        // Save files to output directory
        string p_path = output_directory+"/program.txt";
        string d_path = output_directory+"/data.txt";
        write_memory_file(p_path, program_memory);
        write_memory_file(d_path, data_memory);

    } else {
        cout << "Usage: " << argv[0] << " <main .track filepath> [secondary .track filepath(s)] [-o output_dir]" << endl;
    }

    return 0;
}