#ifndef STITCHER_H
#define STITCHER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

void stitch_program(map<string, vector<string>> &main, vector<string> secondary_filepaths);
vector<string> get_directive_from_file(string filepath, string directive_name);

#endif