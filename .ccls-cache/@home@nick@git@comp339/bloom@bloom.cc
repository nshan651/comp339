#include <iostream>
#include <cstring>
#include <cmath>
#include <functional>
/* #include <openssl/md5.h> */
#include <openssl/sha.h>
#include <openssl/evp.h>

using namespace std;

class BloomFilter {
    int m, k, n;
    int *data;

public:
    BloomFilter(int m, int k) {
        this->m = m;
        this->k = k;
        this->n = 0;
        this->data = new int[m];
        memset(this->data, 0, m*sizeof(int));
    }

    void insert(string element) {
        if (k == 1) {
            int hash1 = h1(element) % m;
            data[hash1] = 1;
        }
        else if (k == 2) {
            int hash1 = h1(element) % m;
            int hash2 = h2(element) % m;
            data[hash1] = 1;
            data[hash2] = 1;
        }
        n++;
    }

    string search(string element) {
        if (k == 1) {
            int hash1 = h1(element) % m;
            if (data[hash1] == 0)
                return "Not in Bloom Filter";
        }
        else if (k == 2) {
            int hash1 = h1(element) % m;
            int hash2 = h2(element) % m;
            if (data[hash1] == 0 || data[hash2] == 0)
                return "Not in Bloom Filter";
        }
        double prob = pow((1.0 - pow((1.0 - 1.0/m), k*n)), k);
        return "Might be in Bloom Filter with false positive probability " + to_string(prob);
    }

    size_t h1(string w) {
        unsigned char *hash = MD5((unsigned char*)w.c_str(), w.length(), NULL);
        char base64_hash[9];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 6);
        return std::hash<string>{}(base64_hash) % 10;
    }

    size_t h2(string w) {
        unsigned char *hash = SHA256((unsigned char*)w.c_str(), w.length(), NULL);
        char base64_hash[9];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 6);
        return std::hash<string>{}(base64_hash) % 10;
    }

    ~BloomFilter() {
        delete[] data;
    }
};

int main() {
    BloomFilter bf(100, 2);
    bf.insert("hello");
    bf.insert("world");
    cout << bf.search("hello"); // "Might be in Bloom Filter with false positive probability 0.00675961"
    cout << bf.search("goodbye"); // "Not in Bloom Filter"
    return 0;
}

