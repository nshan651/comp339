#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <ostream> 
#include <unistd.h>
#include <set>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <random>

using namespace std;
/* Type aliases */
using Shifter = string(*)(const string, const int);
using CipherMap = map<vector<string>, int>;
using CipherIter = vector<vector<string>>::iterator;

const string PROJ_DIR = "./data/";
const int ALPHABET_SIZE = 26;

struct Cipher {
    int num_lines = 10;
    int min_len = 3;
    string dict = PROJ_DIR + "american-english";
    string input = ""; 
    string output = ""; 
};

/* Encoder and decoder */
void encoder(const Cipher &cipher, istream &input, ostream &output);
void decoder(const Cipher &cipher, istream &input, ostream &output);

/* IO streams */
istream &in_stream(string &input);
ostream &out_stream(string &output);

void output_words(vector<string> &words, ostream &output);

int rng(const int min, const int max);
int decode(vector<string> &words, map<string, int> &dictionary);
vector<string> encode(vector<string> &words, int shift);
int parse_args(Cipher &cipher, int argc, char **argv);

string convert_alpha(string &word);
string shift_left(const string word, const int shift);
string shift_right(const string word, const int shift);

vector<string> collect_words(vector<string> &words, Shifter func, const int shift);
vector<string> split_line(string &line, const int min_len);
map<string, int> parse_dict(const Cipher &cipher);
