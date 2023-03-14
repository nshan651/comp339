#include <lib.hh>


hash_func* hash_sha256()
{
    auto hf = [](const string& word) -> size_t {
        unsigned char *hash = SHA256((unsigned char*)word.c_str(), word.length(), NULL);
        char base64_hash[9];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 6);
        return std::hash<string>{}(base64_hash) % 10;
    };
    return new hash_func(hf);
}

hash_func* hash_sha1()
{
    auto hf = [](const string& word) -> size_t {
        unsigned char *hash = SHA1((unsigned char*)word.c_str(), word.length(), NULL);
        char base64_hash[7];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 5);
        return std::hash<string>{}(base64_hash) % 10;
    };
    return new hash_func(hf);
}

hash_func* hash_sha512()
{
    auto hf = [](const string& word) -> size_t {
        unsigned char *hash = SHA512((unsigned char*)word.c_str(), word.length(), NULL);
        char base64_hash[17];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 13);
        return std::hash<string>{}(base64_hash) % 10;
    };
    return new hash_func(hf);
}

hash_func* hash_ripemd160()
{
    auto hf = [](const string& word) -> size_t {
        unsigned char hash[RIPEMD160_DIGEST_LENGTH];
        RIPEMD160((unsigned char*)word.c_str(), word.length(), hash);
        char base64_hash[11];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 8);
        return std::hash<string>{}(base64_hash) % 10;
    };
    return new hash_func(hf);
}

hash_func* hash_whirlpool()
{
    auto hf = [](const string& word) -> size_t {
        unsigned char hash[WHIRLPOOL_DIGEST_LENGTH];
        WHIRLPOOL((unsigned char*)word.c_str(), word.length(), hash);
        char base64_hash[21];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 16);
        return std::hash<string>{}(base64_hash) % 10;
    };
    return new hash_func(hf);
}

/* size_t hash_sha1(const string &word) */ 
/* { */
/*     unsigned char *hash = SHA1((unsigned char*)word.c_str(), word.length(), NULL); */
/*     char base64_hash[7]; */
/*     EVP_EncodeBlock((unsigned char*)base64_hash, hash, 5); */
/*     return std::hash<string>{}(base64_hash) % 10; */
/* } */

/* size_t hash_sha512(const string &word) */ 
/* { */
/*     unsigned char *hash = SHA512((unsigned char*)word.c_str(), word.length(), NULL); */
/*     char base64_hash[17]; */
/*     EVP_EncodeBlock((unsigned char*)base64_hash, hash, 13); */
/*     return std::hash<string>{}(base64_hash) % 10; */
/* } */

/* size_t hash_ripemd160(const string &word) */ 
/* { */
/*     unsigned char hash[RIPEMD160_DIGEST_LENGTH]; */
/*     RIPEMD160((unsigned char*)word.c_str(), word.length(), hash); */
/*     char base64_hash[11]; */
/*     EVP_EncodeBlock((unsigned char*)base64_hash, hash, 8); */
/*     return std::hash<string>{}(base64_hash) % 10; */
/* } */

/* size_t hash_whirlpool(const string &word) */ 
/* { */
/*     unsigned char hash[WHIRLPOOL_DIGEST_LENGTH]; */
/*     WHIRLPOOL((unsigned char*)word.c_str(), word.length(), hash); */
/*     char base64_hash[21]; */
/*     EVP_EncodeBlock((unsigned char*)base64_hash, hash, 16); */
/*     return std::hash<string>{}(base64_hash) % 10; */
/* } */


/* size_t hash_sha3(const string &word) */ 
/* { */
/*     unsigned char *hash = SHA3_256((unsigned char*)word.c_str(), word.length()); */
/*     char base64_hash[9]; */
/*     EVP_EncodeBlock((unsigned char*)base64_hash, hash, 6); */
/*     return std::hash<string>{}(base64_hash) % 10; */
/* } */

/* size_t hash_blake2(const string &word) */ 
/* { */
/*     unsigned char hash[32]; */
/*     BLAKE2s(hash, (unsigned char*)word.c_str(), NULL, sizeof(hash), word.length()); */
/*     char base64_hash[9]; */
/*     EVP_EncodeBlock((unsigned char*)base64_hash, hash, 6); */
/*     return std::hash<string>{}(base64_hash) % 10; */
/* } */
