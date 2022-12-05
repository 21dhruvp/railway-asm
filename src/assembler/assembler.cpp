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
#include <sstream>
#include <iomanip>

#include "../../include/assembler/assembler.h"
#include "../../include/assembler/instructions.h"
#include "../../include/parsing.h"
#include "../../include/errors.h"

using namespace std;

string text_directive_to_program_memory(vector<string> &program, vector<string> &data_labels) {
    /*
    v3.0 hex words addressed
    00: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    10: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    20: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    30: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    40: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    50: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    60: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    70: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    80: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    90: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    a0: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    b0: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    c0: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    d0: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    e0: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    f0: 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000
    */
    // Takes the text directive and converts it into program memory. 16 bit instructions. Maintains program structure but in hex form.
    // string translation = get_machine_code_from_line(program[i], data_labels);

    string file_contents = "v3.0 hex words addressed\n";
    stringstream ss;
    int curr_line = 0;
    int curr_insertion = 0;

    for (size_t i = 0; i < PROGRAM_MEMORY_WIDTH * PROGRAM_MEMORY_WIDTH; i++) {
        bool use_fill = false;
        if (i >= program.size()) {
            use_fill = true;
        }

        if (curr_insertion == 0) {
            ss << hex << setw(2) << setfill('0') << curr_line;
            file_contents += ss.str()+": ";
            ss.str("");
            ss.clear();
        }

        if (!use_fill) {
            string translation = get_machine_code_from_line(program[i], data_labels);
            file_contents += translation;
        } else {
            file_contents += "0000";
        }

        if (curr_insertion == 15) {
            if (curr_line != PROGRAM_MEMORY_WIDTH * PROGRAM_MEMORY_WIDTH) {
                file_contents += "\n";
            }
            curr_line += 16;
            curr_insertion = 0;
        } else {
            file_contents += " ";
            curr_insertion++;
        }
    }

    return file_contents;
}

string data_directive_to_memory(vector<string> &data) {
    /*
    v3.0 hex words addressed
    00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    20: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    30: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    40: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    50: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    60: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    70: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    90: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    a0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    b0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    c0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    d0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    e0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    f0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
    */
    // Takes the data directive and converts it into bytes compatible with Logisim's memory component.
    string file_contents = "v3.0 hex words addressed\n";
    stringstream ss;
    int curr_line = 0;
    int curr_insertion = 0;

    for (size_t i = 0; i < DATA_MEMORY_WIDTH * DATA_MEMORY_WIDTH; i++) {
        bool use_fill = false;
        if (i >= data.size()) {
            use_fill = true;
        }

        if (curr_insertion == 0) {
            ss << hex << setw(2) << setfill('0') << curr_line;
            file_contents += ss.str()+": ";
            ss.str("");
            ss.clear();
        }

        if (!use_fill) {
            string translation = get_data_bytes_from_line(data[i]);
            file_contents += translation;
        } else {
            file_contents += "00";
        }

        if (curr_insertion == 15) {
            if (curr_line != DATA_MEMORY_WIDTH * DATA_MEMORY_WIDTH) {
                file_contents += "\n";
            }
            curr_line += 16;
            curr_insertion = 0;
        } else {
            file_contents += " ";
            curr_insertion++;
        }
    }

    return file_contents;
}