//#include "assignments/wl/word_ladder.h"
#include "word_ladder.h"

// TODO(students): Add your stuff here

#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_set>

using namespace std;

typedef map<string, vector<vector<string>>> Map;

vector<vector<string>> ladders(string start, string end, unordered_set<string>& words_list) {
  vector<vector<string>> result;  // record all the results

  auto n = start.size();              // record length of start

  Map myMap{};
  Map::iterator iter; // define a map iterator

  vector<vector<string>> start_value;         // record the path

  vector<string> start_value_element;
  start_value_element.push_back(start);
  start_value.push_back(start_value_element);

  myMap[start] = start_value;

  while (!myMap.empty()) {
    Map myNewMap;   // used to update myMap
    for (iter = myMap.begin(); iter != myMap.end(); iter++) {
      string word = iter->first;        // key
      if (word == end) {
        auto map_size = myMap[word].size();
        for (size_t i = 0; i < map_size; i++) {
          vector<string> k;
          k = myMap[word][i];
          result.push_back(k);
        }
      } else {
        string new_word;
        for (size_t i = 0; i < n; i++) {
          char current_char = word[i];
          for (char c = 'a'; c <= 'z'; c++) {
            if (c == current_char) {
              continue;
            } else{
              new_word = word;
              new_word[i] = c;
            }

            if (words_list.find(new_word) != words_list.end()) {
              auto map_size = myMap[word].size();
              for (size_t i = 0; i < map_size; i++) {
                vector<string> j;
                j = myMap[word][i];
                j.push_back(new_word);
                myNewMap[new_word].push_back(j);
              }
            }
          }
        }
      }
    }

    for (iter = myNewMap.begin(); iter != myNewMap.end(); iter++) {
      words_list.erase(iter->first);
    }
    myMap = myNewMap;
  }

  sort(result.begin(), result.end());
  return result;
}
      
// int main() {
//     ifstream infile("words.txt");   // open the file
//     vector<string> words_set;
//     string word;
//     while (getline(infile, word)) {
//         if (word.size() > 0) {
//             words_set.push_back(word);
//         }
//     }
//     infile.close();

//     string start, end;
//     cout << "Enter start word (RETURN to quit): ";
//     cin >> start;
//     cout << "Enter destination word: ";
//     cin >> end;

//     vector<vector<string>> result = ladders(start, end, words_set);
//     if (!result.empty()) {
//         cout << "Found ladder: ";

//         for(size_t i = 0; i < result.size(); i++) {
//              for (size_t j = 0; j < result[i].size(); j++) {
//                      cout << result[i][j] << " ";
//              }
//              cout << "\n";
//         }
//     } else {
//         cout << "No ladder found.\n";
//     }

//     return 0;
// }