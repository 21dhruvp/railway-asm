#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <vector>

using namespace std;

void validate(map<string, vector<string>> &program);

void syntax_validate(map<string, vector<string>> &program);
void value_validate(map<string, vector<string>> &program);

bool is_valid_instruction(string &instruction);
bool is_valid_data_type(string &type);

#endif