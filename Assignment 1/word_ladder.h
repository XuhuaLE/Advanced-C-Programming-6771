#ifndef ASSIGNMENTS_WL_WORD_LADDER_H_
#define ASSIGNMENTS_WL_WORD_LADDER_H_

#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <map>
#include <unordered_set>

using namespace std;

// TODO(students): Add some stuff here
typedef map<string, vector<vector<string>>> Map;
vector<vector<string>> ladders(string start, string end, unordered_set<string>& words_list);

#endif  // ASSIGNMENTS_WL_WORD_LADDER_H_