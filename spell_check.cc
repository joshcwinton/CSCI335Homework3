// JOSH WINTON
// CSCI 335 ASSIGNMENT 3 PART 2

#include "quadratic_probing.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

string StringClean(string dirty) {
  std::transform(dirty.begin(), dirty.end(), dirty.begin(), ::tolower);
  if ((dirty[dirty.length() - 1] == ',') ||
      (dirty[dirty.length() - 1] == '.')) {
    dirty = dirty.substr(0, dirty.length() - 1);
  }
  return dirty;
}

template <typename HashTableType>
void CheckSpelling(HashTableType &hash_table, const string &document_filename) {
  cout << "\nChecking Spelling...\n";
  string letters = "abcdefghijklmnopqrstuvwxyz";
  string db_word;
  ifstream db_file(document_filename);
  if (db_file.is_open()) {
    while (db_file >> db_word) {
      db_word = StringClean(db_word);
      if (hash_table.Contains(db_word)) {
        cout << db_word << ": Correct\n";
      } else {
        cout << db_word << ": Incorrect";
        // case a
        for (size_t i = 0; i < db_word.length(); i++) {
          for (size_t j = 0; j < 26; j++) {
            string test = db_word.substr(0, i) + letters[j] + db_word.substr(i);
            if (hash_table.Contains(test)) {
              cout << " -> " << test;
            }
          }
        }

        // case b
        for (size_t i = 0; i < db_word.length()-1; i++) {
          string test = db_word.substr(0, i) + db_word.substr(i+1);
          if (hash_table.Contains(test)) {
            cout << " -> " << test;
          }
        }

        // case c
        for (size_t i = 0; i < db_word.length()-1; i++) {
          string test = db_word;
          char temp = db_word[i];
          char temp2 = db_word[i+1];
          test[i]=temp2;
          test[i+1]=temp;
          if(hash_table.Contains(test)){
            cout << " -> " << test;
          }
        }
        cout << endl;
      }
    }
  }
}

template <typename HashTableType>
void FillDictionary(HashTableType &hash_table,
                    const string &dictionary_filename) {
  cout << "\nFilling Dictionary...\n";

  string db_word;
  ifstream db_file(dictionary_filename);
  if (db_file.is_open()) {
    while (db_file >> db_word) {
      hash_table.Insert(db_word);
    }
  }

  cout << "\nDictionary Filled.\n" << hash_table.getNumberofElements();
}

// sample main for program spell_check
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>"
         << endl;
    return 0;
  }

  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);

  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl;

  // Call functions implementing the assignment requirements.
  HashTableQuadratic<string> probing_table;
  FillDictionary(probing_table, dictionary_filename);
  CheckSpelling(probing_table, document_filename);
  return 0;
}
