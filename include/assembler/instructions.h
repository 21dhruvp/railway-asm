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
// 01010 001 000 00000


// 5 Bit instruction itentifier with control signals. 16 bit total instruction width.
enum class Instruction {
    // Structure is as follows:
    // WriteReg? Imm? Operation? MemRead? MemWrite?
    //     0        0      0        0           0
    //
    // ADD & SUB:
    // name  Rd  Rn  Rm  filler
    // 00000 000 000 000 00
    //
    // ADD & SUB imm:
    // name  Rd  Rn  imm
    // 00000 000 000 00000
    //
    // GET
    // name  Rd  label Rn  filler
    // 00000 000 000   000 00
    //
    // GET imm
    // name  Rd  label imm
    // 00000 000 000   00000

    ADD,    // 10000
    ADDimm, // 11000
    SUB,    // 10100
    SUBimm, // 11100
    GET,    // 10010
    GETimm, // 11010
};

string get_machine_code_from_line(string &line, vector<string> &data_labels);
string get_data_bytes_from_line(string &line);

#endif