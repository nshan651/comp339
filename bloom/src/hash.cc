#include <lib.hh>

hash_func* hash_sha256()
{
    auto hf = [](const string& word, const int m) -> size_t {
        unsigned char *hash = SHA256((unsigned char*)word.c_str(), word.length(), NULL);
        char base64_hash[9];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 6);
        return std::hash<string>{}(base64_hash) % m;
    };
    return new hash_func(hf);
}

hash_func* hash_sha512()
{
    auto hf = [](const string& word, const int m) -> size_t {
        unsigned char *hash = SHA512((unsigned char*)word.c_str(), word.length(), NULL);
        char base64_hash[17];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 13);
        return std::hash<string>{}(base64_hash) % m;
    };
    return new hash_func(hf);
}

hash_func* hash_ripemd160()
{
    auto hf = [](const string& word, const int m) -> size_t {
        unsigned char hash[RIPEMD160_DIGEST_LENGTH];
        RIPEMD160((unsigned char*)word.c_str(), word.length(), hash);
        char base64_hash[11];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 8);
        return std::hash<string>{}(base64_hash) % m;
    };
    return new hash_func(hf);
}

hash_func* hash_whirlpool()
{
    auto hf = [](const string& word, const int m) -> size_t {
        unsigned char hash[WHIRLPOOL_DIGEST_LENGTH];
        WHIRLPOOL((unsigned char*)word.c_str(), word.length(), hash);
        char base64_hash[21];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 16);
        return std::hash<string>{}(base64_hash) % m;
    };
    return new hash_func(hf);
}

hash_func* hash_blake2() 
{
    auto hf = [](const string& word, const int m) -> size_t {
        unsigned char hash[BLAKE2B_OUTBYTES];
        blake2b(hash, word.c_str(), NULL, BLAKE2B_OUTBYTES, word.length(), 0);
        char base64_hash[BLAKE2B_OUTBYTES * 2];
        EVP_EncodeBlock(reinterpret_cast<unsigned char*>(base64_hash), hash, BLAKE2B_OUTBYTES);
        return std::hash<std::string>{}(base64_hash) % m;
    };
    return new hash_func(hf);
}
