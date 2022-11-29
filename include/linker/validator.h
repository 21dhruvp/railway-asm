#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <vector>

using namespace std;

void validate(vector<string> &program);

void syntax_validate(vector<string> &program);
void value_validate(vector<string> &program);

#endif