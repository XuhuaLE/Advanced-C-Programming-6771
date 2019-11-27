#include <iostream>

// #include "assignments/wl/lexicon.h"
// #include "assignments/wl/word_ladder.h"

#include "lexicon.h"
#include "word_ladder.h"

using namespace std;

int main() {

  // auto lexicon = GetLexicon("assignments/wl/words.txt");
  auto lexicon = GetLexicon("words.txt");

  // TODO(students): Replace this with your code

  string start, end;
  cout << "Enter start word (RETURN to quit): ";
  cin >> start;
  cout << "Enter destination word: ";
  cin >> end;

  vector<vector<string>> result = ladders(start, end, lexicon);
  if (!result.empty()) {
    cout << "Found ladder: ";

    for(size_t i = 0; i < result.size(); i++) {
            for (size_t j = 0; j < result[i].size(); j++) {
                    cout << result[i][j] << " ";
            }
            cout << "\n";
    }
  } else {
    cout << "No ladder found.\n";
  }

  // for (const auto& word : lexicon) {
  //   std::cout << word << '\n';
  // }
  return 0;
}
