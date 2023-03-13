#include <iostream>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

string convert_alpha(string &word);
map<string, int> parse_dict(string &dict);
vector<string> split_line(string &line, const int min_len);
