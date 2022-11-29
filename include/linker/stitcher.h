#ifndef STITCHER_H
#define STITCHER_H

#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> stitch_program(vector<string> main, map<string, vector<string>> secondary_filepaths);

#endif