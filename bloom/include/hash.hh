#include <vector>
#include <functional>
#include <openssl/sha.h>
#include <openssl/whrlpool.h>
#include <openssl/ripemd.h>
#include <openssl/evp.h>

using namespace std;

using lamb_hash = function<size_t(const string&, const int)>;

inline auto sha256 = [](const string& word, const int m) -> size_t {
    unsigned char *hash = SHA256((unsigned char*)word.c_str(), word.length(), NULL);
    char base64_hash[9];
    EVP_EncodeBlock((unsigned char*)base64_hash, hash, 6);
    return std::hash<string>{}(base64_hash) % m;
};

inline auto sha512 = [](const string& word, const int m) -> size_t {
    unsigned char *hash = SHA512((unsigned char*)word.c_str(), word.length(), NULL);
    char base64_hash[17];
    EVP_EncodeBlock((unsigned char*)base64_hash, hash, 13);
    return std::hash<string>{}(base64_hash) % m;
};

inline auto ripemd160 = [](const string& word, const int m) -> size_t {
    unsigned char hash[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160((unsigned char*)word.c_str(), word.length(), hash);
    char base64_hash[11];
    EVP_EncodeBlock((unsigned char*)base64_hash, hash, 8);
    return std::hash<string>{}(base64_hash) % m;
};

inline auto whirlpool = [](const string& word, const int m) -> size_t {
    unsigned char hash[WHIRLPOOL_DIGEST_LENGTH];
    WHIRLPOOL((unsigned char*)word.c_str(), word.length(), hash);
    char base64_hash[21];
    EVP_EncodeBlock((unsigned char*)base64_hash, hash, 16);
    return std::hash<string>{}(base64_hash) % m;
};

/** Retrieve the hashset based on desired k */
vector<lamb_hash> get_hashset(int k)
{
    /* Define an array of hash functions to use */
    vector<lamb_hash> hashes;
    hashes.push_back(sha512);
    hashes.push_back(whirlpool);
    hashes.push_back(sha256);
    hashes.push_back(ripemd160);

    /* Slice the list of available hash functions according to k */
    const int end_slice = k < hashes.size() ? k : hashes.size();
    const vector<lamb_hash> hash_set(hashes.begin(), hashes.begin() + end_slice);
    return hash_set;
}
