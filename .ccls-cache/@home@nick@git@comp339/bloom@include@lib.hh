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
/* #include <openssl/blake2.h> */
#include <openssl/whrlpool.h>
#include <openssl/ripemd.h>
#include <openssl/evp.h>

using namespace std;

/* typedef size_t (*hash_func)(const string &); */

using hash_func = function<size_t(const string&)>;

hash_func* hash_sha256();
hash_func* hash_sha512();
hash_func* hash_sha1();
hash_func* hash_ripemd160();
hash_func* hash_whirlpool();

string convert_alpha(string &word);
map<string, int> parse_dict(string &dict);
vector<string> split_line(string &line, const int min_len);

/* hash.cc */
/* size_t hash_sha1(const string &word); */ 
/* size_t hash_sha512(const string &word); */
/* size_t hash_ripemd160(const string &word); */
/* size_t hash_whirlpool(const string &word); */

/* size_t hash_sha3(const string &word); */
/* size_t hash_blake2(const string &word); */

