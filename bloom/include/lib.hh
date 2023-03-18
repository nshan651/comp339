#include <iostream>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

/* OPENSSL IMPORTS */
/* #include <openssl/md5.h> */ // DEPRECATED
#include <openssl/sha.h>
#include <openssl/whrlpool.h>
#include <openssl/ripemd.h>
#include <openssl/evp.h>
#include <blake2.h>

using namespace std;
using hash_func = function<size_t(const string&, const int)>;

hash_func* hash_sha256();
hash_func* hash_sha512();
hash_func* hash_sha1();
hash_func* hash_ripemd160();
hash_func* hash_whirlpool();
hash_func* hash_blake2();

string convert_alpha(string &word);
map<string, int> parse_dict(string &dict);
vector<string> split_line(string &line, const int min_len);
