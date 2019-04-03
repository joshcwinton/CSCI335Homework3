// JOSH WINTON
// CSCI 335 ASSIGNMENT 3 PART 2

#include "quadratic_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string StringClean(string dirty){
  std::transform(dirty.begin(), dirty.end(), dirty.begin(), ::tolower);
  if((dirty[dirty.length() == ',']) || (dirty[dirty.length() == '.'])){
    dirty = dirty.substr(0,dirty.length());
  }
  return dirty;
}

template <typename HashTableType>
void CheckSpelling(HashTableType &hash_table, const string &document_filename){
  cout << "\nChecking Spelling...\n";

  string db_word;
  ifstream db_file(document_filename);
  if(db_file.is_open()){
    while(db_file >> db_word){
      db_word = StringClean(db_word);
      if(hash_table.Contains(db_word)){
        cout << db_word << ": Correct\n";
      } else {
        cout << db_word << ": Incorrect\n";
        // ADD a, b, and c here!!!!
      }
    }
  }
}

template <typename HashTableType>
void FillDictionary(HashTableType &hash_table, const string &dictionary_filename){
  cout << "\nFilling Dictionary...\n";

  string db_word;
  ifstream db_file(dictionary_filename);
  if(db_file.is_open()){
    while(db_file >> db_word){
      hash_table.Insert(db_word);
    }
  }

  cout << "\nDictionary Filled.\n" << hash_table.getNumberofElements();
}

// sample main for program spell_check
int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
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
