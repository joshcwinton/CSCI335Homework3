Josh Winton - CSCI 335 - Project 3

Part 1A and 1B Completed:
- Wrote a loop to read words from given text file and insert them into hash table using built-in insert function
- Printed total number of elements in the table, the table size, the load factor, total collisions and average collisions.
- Wrote a loop to read through given query file and check whether words are in the hash table
- Added code to count probes and collisions, printed number of probes used to find each word
- Wrote code for linear hashing (removed offset variable and instead incremented current location by 1)

Part 2 Completed:
- Wrote code for double hashing using a second function to apply another hash function
- Ran into an issue where I got segmentation faults for prime numbers higher than 13, it turned out I was misapplying my second hash function
- R is 97
- strange namespace/redefinition error, fixed by placing functions defined within anonymous namespace in new source file and including it where needed

Part 3 Complete:
- Wrote a function that fills a hash table with dictionary words and then reads through the given document and tells whether each word is in the dictionary or not.
- Wrote a function to clean up text (handles periods, commas, case)
- Wrote loops for cases a-c that check hash table for similar spellings
- Dictionary doesn't include words like "I" or some contractions but I didn't worry about that
- "law" generates "wa" and "la" based on case b but both are in the dictionary provided

Instructions for Running:
make clean
make all
./create_and_test_hash words.txt query_words.txt <hashing-flag>
./spell_check document1.txt wordsEn.txt

Input files included.
