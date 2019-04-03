// Josh Winton
// Main file for Assignment 3 Part 1 and 2

#include "double_hash.h"
#include "linear_probing.h"
#include "quadratic_probing.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table,
                              const string &words_filename,
                              const string &query_filename) {
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  hash_table.MakeEmpty();

  // Read words from input file and fill hash table:
  string db_line;
  ifstream db_file(words_filename);
  if (db_file.is_open()) {
    while (getline(db_file, db_line)) {
      hash_table.Insert(db_line);
    }
  }

  // Print hash table data:
  cout << "\nFilling Hash Table..." << endl << endl;
  cout << "Table Statistics:\n";
  cout << "Collisions: " << hash_table.getCollisions() << endl;
  cout << "Number of items: " << hash_table.getNumberofElements() << endl;
  cout << "Size of hash table: " << hash_table.getTableSize() << endl;
  cout << "Load factor: " << hash_table.getLoadFactor() << endl;
  cout << "Avg. number of collisions: " << hash_table.getAverageCollisions()
       << endl;

  // Queries:
  cout << "\nQueries:\n";
  string queryline;
  ifstream queryfile(query_filename);
  if (queryfile.is_open()) {
    while (getline(queryfile, queryline)) {
      if (hash_table.Contains(queryline)) {
        cout << queryline << ": Found in " << hash_table.getProbes()
             << " probes." << endl;
      } else {
        cout << queryline << ": Not Found in " << hash_table.getProbes()
             << " probes." << endl;
      }
    }
  }
}

// Sample main for program create_and_test_hash
int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>"
         << endl;
    return 0;
  }

  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename,
                             query_filename);
  } else if (param_flag == "quadratic") {
    HashTableQuadratic<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename,
                             query_filename);
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename,
                             query_filename);
  } else {
    cout << "Unknown tree type " << param_flag
         << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
