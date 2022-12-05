#include <string>
#include <vector>
#include <map>
#include <set>

#include "../../include/linker/validator.h"
#include "../../include/parsing.h"
#include "../../include/assembler/instructions.h"
#include "../../include/errors.h"
#include "../../include/utility.h"

using namespace std;

void validate(map<string, vector<string>> &program) {
    syntax_validate(program);
    value_validate(program);

    return;
}

void syntax_validate(map<string, vector<string>> &program) {
    //*text directive checking
    int line = 1;
    vector<string> instructions = program["program"];
    for (const string &instruction : instructions) {
        vector<string> tokenized = tokenize(instruction, " ");

        if (instruction.find("(") != string::npos || instruction.find(")") != string::npos) {
            string message = Color().RED+"error in text directive on line #"+to_string(line)+Color().reset+": Invalid position for directive opening or closing!";
            throw railway_syntax_error(&message[0]);
        }

        if (!is_valid_instruction(tokenized[0])) {
            string message = Color().RED+"error in text directive on line #"+to_string(line)+Color().reset+": Invalid instruction '"+tokenized[0]+"'!";
            throw railway_syntax_error(&message[0]);
        }

        if ((tokenized[0] != "get" && tokenized[0] != "put" && tokenized[0] != "lda" && tokenized[0] != "dne") && tokenized.size() < 4) {
            string message = Color().RED+"error in text directive on line #"+to_string(line)+Color().reset+": Missing arguments! ("+instruction+")";
            throw railway_syntax_error(&message[0]);
        }

        if ((tokenized[0] == "get" || tokenized[0] == "put" || tokenized[0] == "lda") && tokenized.size() < 3) {
            string message = Color().RED+"error in text directive on line #"+to_string(line)+Color().reset+": Missing arguments! ("+instruction+")";
            throw railway_syntax_error(&message[0]);
        }

        if ((tokenized[0] != "lda" && tokenized[0] != "dne") && tokenized[1].at(0) != 'r') {
            string message = Color().RED+"error in text directive on line #"+to_string(line)+Color().reset+": Argument 1 must be a register! ("+instruction+")";
            throw railway_syntax_error(&message[0]);
        }

        if ((tokenized[0] != "lda" && tokenized[0] != "dne" && tokenized[0] != "get" && tokenized[0] != "put") && tokenized[2].at(0) != 'r') {
            string message = Color().RED+"error in text directive on line #"+to_string(line)+Color().reset+": Argument 2 must be a register! ("+instruction+")";
            throw railway_syntax_error(&message[0]);
        }

        line++;
    }

    //*data directive checking
    line = 1;
    instructions = program["data"];
    for (const string &instruction : instructions) {
        vector<string> tokenized = tokenize(instruction, " ");

        if (tokenized.size() != 3) {
            string message = Color().RED+"error in data directive on line #"+to_string(line)+Color().reset+": Invalid declaration!";
            throw railway_syntax_error(&message[0]);
        }

        if (tokenized[0].at(0) != '[') {
            string message = Color().RED+"error in data directive on line #"+to_string(line)+Color().reset+": Must begin label & type declaration with a '['!";
            throw railway_syntax_error(&message[0]);
        }

        if (tokenized[1].at(tokenized[1].size() - 1) != ']') {
            string message = Color().RED+"error in data directive on line #"+to_string(line)+Color().reset+": Must end label & type declaration with a ']'!";
            throw railway_syntax_error(&message[0]);
        }

        if (!is_valid_data_type(tokenized[1].replace(((int) tokenized[1].size()) - 1, 1, ""))) {
            string message = Color().RED+"error in data directive on line #"+to_string(line)+Color().reset+": Invalid data type '"+tokenized[1].replace(((int) tokenized[1].size()) - 1, 1, "")+"'!";
            throw railway_syntax_error(&message[0]);
        }

        line++;
    }

    return;
}

void value_validate(map<string, vector<string>> &program) {
    // Check line by line for value errors. (invalid registers, integers larger than 6 bits, etc.)
    
    //*text directive checking
    int line = 1;
    vector<string> instructions = program["program"];
    vector<string> data_labels = calculate_data_labels(program["data"]);
    for (const string &instruction : instructions) {
        vector<string> tokenized = tokenize(instruction, " ");
        
        if (tokenized[0] != "lda" && tokenized[0] != "dne") {
            for (int i = 1; i < tokenized.size(); i++) {

                if (tokenized[i].at(0) == 'r' && tokenized[i].size() >= 2) {
                    int r_val = tokenized[i].at(1) - '0';

                    if (r_val < 0 || r_val > 7) {
                        string message = Color().RED+"error in text directive on line #"+to_string(line)+Color().reset+": Register value is too big!";
                        throw railway_syntax_error(&message[0]);
                    } 
                } else {
                    bool is_label = false;
                    for (size_t j = 0; j < data_labels.size(); j++) {
                        if (tokenized[i] == data_labels[j]) {
                            is_label = true;
                            break;
                        }
                    }

                    if (!is_label) {
                        int imm_val = fast_atoi(&tokenized[i][tokenized[i].size() - 1]);
                        if (imm_val < 0 || imm_val > 31) {
                            string message = Color().RED+"error in text directive on line #"+to_string(line)+Color().reset+": Immediate value is too big!";
                            throw railway_syntax_error(&message[0]);
                        }
                    }
                }

            }
        }

        line++;
    }
    //*data directive checking for reused labels
    line = 1;
    instructions = program["data"];
    set<string> labels;
    int additions = 0;
    
    for (const string &instruction : instructions) {
        vector<string> tokenized = tokenize(instruction, " ");

        labels.insert(tokenized[0].replace(0, 1, ""));

        additions++;
        line++;
    }

    if ((int) labels.size() != additions) {
        string message = Color().YELLOW+"some labels are being reused! please check data segment in all files!"+Color().reset;
        throw railway_syntax_error(&message[0]);
    }

    return;
}

bool is_valid_instruction(string &instruction) {
    bool is_valid = false;

    string instructions[6] = {"get", "put", "add", "sub", "lda", "dne"};
    int size = 6;

    for (int i = 0; i < size; i++) {
        if (instructions[i] == instruction) {
            is_valid = true;
            break;
        }
    }

    return is_valid;
}


bool is_valid_data_type(string &type) {
    bool is_valid = false;

    string types[1] = {"integer"};
    int size = 1;

    for (int i = 0; i < size; i++) {
        if (types[i] == type) {
            is_valid = true;
            break;
        }
    }

    return is_valid;
}