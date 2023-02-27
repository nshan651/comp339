#include <iostream>
#include <cstring>
#include <cmath>
#include <functional>
/* #include <openssl/md5.h> */ // DEPRECATED
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <CLI/CLI.hpp>

using namespace std;

class BloomFilter 
{
    int m, k, n;
    int *data;

public:
    BloomFilter(int m, int k) 
    /** Bloom filter constructor.
        Arguments:
            m | the number of bits
            k | the number of hash functions
     */
    {
        this->m = m;
        this->k = k;
        this->n = 0;
        this->data = new int[m];
        memset(this->data, 0, m*sizeof(int));
    }

    void insert(string element)
    /** Insert hash into Bloom Filter. */
    {
        if (k == 1) {
            int hash1 = hash_sha256(element) % m;
            data[hash1] = 1;
        }
        else if (k == 2) {
            int hash1 = hash_sha256(element) % m;
            int hash2 = hash_sha256(element) % m;
            data[hash1] = 1;
            data[hash2] = 1;
        }
        n++;
    }

    string search(string element)
    /** Search for a hash in the Bloom Filter. */
    {
        if (k == 1) {
            int hash1 = hash_sha256(element) % m;
            if (data[hash1] == 0)
                return "Not in Bloom Filter\n";
        }
        else if (k == 2) {
            int hash1 = hash_sha256(element) % m;
            int hash2 = hash_sha256(element) % m;
            if (data[hash1] == 0 || data[hash2] == 0)
                return "Not in Bloom Filter";
        }
        double prob = pow((1.0 - pow((1.0 - 1.0/m), k*n)), k);
        return "Might be in Bloom Filter with false positive probability " + to_string(prob) + "\n";
    }

    size_t hash_sha256(string w) 
    {
        unsigned char *hash = SHA256((unsigned char*)w.c_str(), w.length(), NULL);
        char base64_hash[9];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 6);
        return std::hash<string>{}(base64_hash) % 10;
    }

    ~BloomFilter() 
    /** Destructor. */
    {
        delete[] data;
    }
};

int main(int argc, char **argv) 
{

    int m = 0;
    int k = 0;

    CLI::App app("BloomFilter CLI");

    /* app.add_option("-m", m, "Number of bits")->required(); */
    app.add_option("-m", m, "Number of bits")->default_val(100);
    app.add_option("-k", k, "Number of hash functions")->default_val(2);

    CLI11_PARSE(app, argc, argv);

    BloomFilter bf(m, k);

    bf.insert("hello");
    bf.insert("world");
    // "Might be in Bloom Filter with false positive probability 0.00675961"
    cout << bf.search("hello"); 
    // Not in Bloom Filter
    cout << bf.search("goodbye"); 
    return 0;
}

