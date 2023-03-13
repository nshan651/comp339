#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <functional>
/* #include <openssl/md5.h> */
#include <openssl/sha.h>
#include <cmath>

class BloomFilter {
public:
    BloomFilter(int m, int k) : m(m), k(k), data(m, 0), n(0) {}

    void insert(std::string element) {
        if (k == 1) {
            int hash1 = h2(element) % m;
            data[hash1] = 1;
        }
        else if (k == 2) {
            int hash1 = h2(element) % m;
            int hash2 = h2(element) % m;
            data[hash1] = 1;
            data[hash2] = 1;
        }
        n++;
    }

    std::string search(std::string element) {
        if (k == 1) {
            int hash1 = h2(element) % m;
            if (data[hash1] == 0) {
                return "Not in Bloom Filter";
            }
        }
        else if (k == 2) {
            /* int hash1 = h1(element) % m; */
            int hash1 = h2(element) % m;
            int hash2 = h2(element) % m;
            if (data[hash1] == 0 || data[hash2] == 0) {
                return "Not in Bloom Filter";
            }
        }
        double prob = pow(1.0 - pow(1.0 - 1.0/m, k*n), k);
        return "Might be in Bloom Filter with false positive probability " + std::to_string(prob);
    }
    std::vector<int> getData() {
        return data;
    }

private:
    int m;
    int k;
    std::vector<int> data;
    int n;

    /* int h1(std::string w) { */
    /*     unsigned char md5_result[MD5_DIGEST_LENGTH]; */
    /*     MD5((unsigned char*)w.c_str(), w.size(), md5_result); */
    /*     std::string md5_str((char*)md5_result, MD5_DIGEST_LENGTH); */
    /*     return std::hash<std::string>{}(md5_str) % 10; */
    /* } */

    int h2(std::string w) {
        unsigned char sha256_result[SHA256_DIGEST_LENGTH];
        SHA256((unsigned char*)w.c_str(), w.size(), sha256_result);
        std::string sha256_str((char*)sha256_result, SHA256_DIGEST_LENGTH);
        return std::hash<std::string>{}(sha256_str) % 10;
    }
};

int main() {
    BloomFilter bf(100, 2);
    bf.insert("Hello");
    std::vector<int> data = bf.getData();
    std::cout << "Data: ";
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
    std::cout << bf.search("Hello") << std::endl;
    std::cout << bf.search("ge") << std::endl;
    std::cout << bf.search("No Way This is in") << std::endl;
    return 0;
}
