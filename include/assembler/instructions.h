/**
 * instructions.h
 * railway-asm
 * 
 * Created on November 28th, 2022 by Ryan Monaghan
 * Copyright 2022 Ryan Monaghan. All rights reserved.
*/

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <string>

using namespace std;

// 5 Bit instruction itentifier with control signals. 16 bit total instruction width.
enum class Instruction {
    // Structure is as follows:
    // Needs ALU? Is immediate? Two's compliment? Get memory? Put memory?
    //     0           0              0                 0        0
    //
    // Instruction (Registers):
    // name  Rd  Rn  Rm  Filler
    // 00000 000 000 000 000
    //
    // Instruction (Immediate):
    // name  Rd  Rn  imm
    // 00000 000 000 000000

    ADD,    // 10000
    ADDimm, // 11000
    SUB,    // 10100
    SUBimm, // 11100
    GET,    // 10010
    GETimm, // 01010
    PUT,    // 10001
    PUTimm, // 11001
};

string get_machine_code_from_line(string &line);
string get_data_bytes_from_line(string &line);

#endif