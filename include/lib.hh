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
using CipherIter = vector<vector<string>>;

const string PROJ_DIR = "./data/";
const int ALPHABET_SIZE = 26;

struct Cipher {
    istream &input = cin;
    ostream &output = cout;
    int num_lines;
    int min_len;
    string dict;
    string std_in; 
    string std_out; 

    /* Constructor reference istream and ostream by passing in defaults */
    Cipher(istream& input_ = cin, 
            ostream& output_ = cout, 
            int num_lines_ = 10, 
            int min_len_ = 3, 
            string dict_ = PROJ_DIR + "american-english",
            string std_in_ = "",
            string std_out_ = ""
        )
        : input{input_}, 
          output{output_}, 
          num_lines{num_lines_}, 
          min_len{min_len_}, 
          dict{dict_}, 
          std_in{std_in_}, 
          std_out{std_out_} {}
};

Cipher build_cipher(int argc, char **argv);
/* Encoder */
CipherMap encoder(const Cipher &cipher, istream &input, ostream &output);
CipherIter read_text(Cipher cipher, istream &input);
CipherIter gen_text(const Cipher &cipher);

CipherMap decoder(const Cipher &cipher);

/* IO streams */
istream &in_stream(string &input);
ostream &out_stream(string &output);

string strip_metadata(string &nline);

int rng(const int min, const int max);
int decode(vector<string> &words, map<string, int> &dictionary);
vector<string> encode(vector<string> &words, int shift);

string convert_alpha(string &word);
string shift_left(const string word, const int shift);
string shift_right(const string word, const int shift);

vector<string> collect_words(vector<string> &words, 
                             Shifter func, 
                             ostream &output, 
                             const int shift);
vector<string> split_line(string &line, const int min_len);
map<string, int> parse_dict(const Cipher &cipher);
void output_words(vector<string> &words, ostream &output);
