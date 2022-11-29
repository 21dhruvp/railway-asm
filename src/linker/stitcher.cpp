#include <vector>
#include <map>
#include <string>

#include "../../include/linker/stitcher.h"
#include "../../include/parsing.h"
#include "../../include/utility.h"

using namespace std;

void stitch_program(map<string, vector<string>> &main, vector<string> secondary_filepaths) {
    vector<string> stitched;

    for (const auto &directives : main) {
        string key = directives.first;

        for (size_t i = 0; i < main[key].size(); i++) {
            trim(main[key][i]);

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
                for (size_t j = 0; j < stitchable.size(); i++) {
                    main[key].insert(main[key].begin() + j, stitchable[j]);
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