#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <ostream> 
#include <set>
#include <cctype>
#include <cstdlib>
#include <cstring>

using namespace std;

/* const string PROJ_DIR = "/home/runner/Project-1-Caesar-Cipher-comp-339-439-ds/data/"; */
const string PROJ_DIR = "./data/";
const int ALPHABET_SIZE = 26;

struct Cipher {
    bool encrypt = false;
    int num_lines;
    int min_len = 3;
    string dict_file = PROJ_DIR + "american-english";
    string input_file = PROJ_DIR + "decrypt.txt";
    string output_file; 
};

/* #ifndef CAESER_TEST_HH */
/* #define CAESER_TEST_HH */ 

int decoder(vector<string> &words, map<string, int> &dictionary);
int encoder(vector<string> &words, int shift);
/* Utils defs */
string convert_alpha(string &word);
vector<string> split_line(string &line, const int min_len);
map<string, int> parse_dict(const string &filename);

/* #endif */
