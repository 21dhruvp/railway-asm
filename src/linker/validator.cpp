#include <string>
#include <vector>

#include "../../include/linker/validator.h"
#include "../../include/errors.h"

using namespace std;

void validate(vector<string> &program) {
    syntax_validate(program);
    value_validate(program);

    return;
}

void syntax_validate(vector<string> &program) {
    // TODO: Check line by line for syntax errors. (invalid instructions, wrong ordering of parameters, unclosed directives, etc.)

    return;
}
void value_validate(vector<string> &program) {
    // TODO: Check line by line for value errors. (invalid registers, integers larger than 6 bits, etc.)
    
    return;
}