#include <vector>
#include <functional>
#include <openssl/sha.h>
#include <openssl/whrlpool.h>
#include <openssl/ripemd.h>
#include <openssl/evp.h>
#include <blake2.h>

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

/* inline auto blake2 = [](const string& word, const int m) -> size_t { */
/*     unsigned char hash[BLAKE2B_OUTBYTES]; */
/*     blake2b(hash, word.c_str(), NULL, BLAKE2B_OUTBYTES, word.length(), 0); */
/*     char base64_hash[BLAKE2B_OUTBYTES * 2]; */
/*     EVP_EncodeBlock(reinterpret_cast<unsigned char*>(base64_hash), hash, BLAKE2B_OUTBYTES); */
/*     return std::hash<string>{}(base64_hash) % m; */
/* }; */
