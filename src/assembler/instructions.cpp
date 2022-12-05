/**
 * instructions.cpp
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <iostream>

#include "../../include/assembler/instructions.h"
#include "../../include/utility.h"
#include "../../include/errors.h"

using namespace std;

string get_machine_code_from_line(string &line, vector<string> &data_labels) {
    // Takes a line of code and converts it to machine code based on the inferred instruction.
    string compiled;
    Instruction instruction = Instruction::ADD;
    vector<string> interpretable = tokenize(line, " ");
    string instruction_name = interpretable[0];

    // instruction interpretation
    if (instruction_name == "add") {
        if (interpretable[interpretable.size() - 1].at(0) == 'r') {
            instruction = Instruction::ADD;
            compiled += "10000";
        } else {
            instruction = Instruction::ADDimm;
            compiled += "11000";
        }

        compiled += binary_n_bit_representation(interpretable[1].at(1) - '0', 3);
        compiled += binary_n_bit_representation(interpretable[2].at(1) - '0', 3);

        if (instruction == Instruction::ADDimm) {
            compiled += binary_n_bit_representation(fast_atoi(interpretable[3].c_str()), 5);
        } else {
            compiled += "00";
            compiled += binary_n_bit_representation(interpretable[3].at(1) - '0', 3);
        }
    } else if (instruction_name == "sub") {
        if (interpretable[interpretable.size() - 1].at(0) == 'r') {
            instruction = Instruction::SUB;
            compiled += "10100";
        } else {
            instruction = Instruction::SUBimm;
            compiled += "11100";
        }

        compiled += binary_n_bit_representation(interpretable[1].at(1) - '0', 3);
        compiled += binary_n_bit_representation(interpretable[2].at(1) - '0', 3);

        if (instruction == Instruction::SUBimm) {
            compiled += binary_n_bit_representation(fast_atoi(interpretable[3].c_str()), 5);
        } else {
            compiled += "00";
            compiled += binary_n_bit_representation(interpretable[3].at(1) - '0', 3);
        }
    } else if (instruction_name == "get") {
        if (interpretable[interpretable.size() - 1].at(0) == 'r') {
            instruction = Instruction::GET;
            compiled += "10010";
        } else {
            instruction = Instruction::GETimm;
            compiled += "01010";
        }

        compiled += binary_n_bit_representation(interpretable[1].at(1) - '0', 3);

        int matched = -1;
        for (size_t i = 0; i < data_labels.size(); i++) {
            if (data_labels[i] == interpretable[2]) {
                matched = i;
                break;
            }
        }

        if (matched == -1) {
            string message = Color().RED+"error in text directive"+Color().reset+": Label '"+interpretable[2]+"' does not exist!";
            throw railway_syntax_error(&message[0]);
        }
        compiled += binary_n_bit_representation(matched, 3);

        if (instruction == Instruction::GETimm) {
            compiled += binary_n_bit_representation(fast_atoi(interpretable[3].c_str()), 5);
        } else {
            compiled += "00";
            compiled += binary_n_bit_representation(interpretable[3].at(1) - '0', 3);
        }
    } else if (instruction_name == "put") {
        if (interpretable[interpretable.size() - 1].at(0) == 'r') {
            instruction = Instruction::PUT;
            compiled += "10001";
        } else {
            instruction = Instruction::PUTimm;
            compiled += "11001";
        }

        int matched = -1;
        for (size_t i = 0; i < data_labels.size(); i++) {
            if (data_labels[i] == interpretable[2]) {
                matched = i;
                break;
            }
        }

        if (matched == -1) {
            string message = Color().RED+"error in text directive"+Color().reset+": Label '"+interpretable[2]+"' does not exist!";
            throw railway_syntax_error(&message[0]);
        }

        compiled += binary_n_bit_representation(matched, 3);

        if (instruction == Instruction::PUTimm) {
            compiled += binary_n_bit_representation(fast_atoi(interpretable[3].c_str()), 5);
        } else {
            compiled += "00";
            compiled += binary_n_bit_representation(interpretable[3].at(1) - '0', 3);
        }
    }

    int result = 0;

    for(size_t i = 0; i < compiled.length(); i++) {
        result <<= 1;
        result += compiled[i] == '1' ? 1 : 0;
    }  

    stringstream ss;
    ss << hex << setw(4) << setfill('0')  << result;

    compiled = ss.str();

    return compiled;
}


string get_data_bytes_from_line(string &line) {
    // Takes a line from the data directive and computes the offsets for where it will be stored.
    string bytes;

    vector<string> ingest = tokenize(line, " ");

    bytes = binary_n_bit_representation(fast_atoi(ingest[2].c_str()), 8);

    int result = 0;

    for(size_t i = 0; i < bytes.length(); i++) {
        result <<= 1;
        result += bytes[i] == '1' ? 1 : 0;
    }  

    stringstream ss;
    ss << hex << setw(2) << setfill('0')  << result;

    bytes = ss.str();
    
    return bytes;
}