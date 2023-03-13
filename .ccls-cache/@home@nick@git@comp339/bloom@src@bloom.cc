#include <lib.hh>
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
    BloomFilter(const int m, const int k) 
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
        for (int i = 0; i < sizeof(data); i++)
            data[i] = 0;
    }

    void insert(const string &element)
    /** Insert hash into Bloom Filter. */
    {
        for (int i = 1; i <= k; i++) {
            int hash = hash_sha256(element) % m;
            data[hash] = 1;
        }
        n++;
    }

    string search(const string &element)
    /** Search for a hash in the Bloom Filter. */
    {
        /* vector<size_t> vhash; */
        vector<size_t> vhash;
        /* Collect hashes for k */
        for (int i = 0; i < k; i++) {
            size_t hash = hash_sha256(element) % m;
            vhash.push_back(hash);
        }
        /* Check if hashes in vhash are found in filter */
        for (size_t hash : vhash) {
            cout << "RESULT OF DATA[HASH]: " << data[hash] << "\n";
            if (data[hash] == 0)
                return "Not in Bloom Filter\n";
        }
        
        double prob = pow((1.0 - pow((1.0 - 1.0/m), k*n)), k);
        return "Might be in Bloom Filter with false positive probability " + to_string(prob) + "\n";
    }

    size_t hash_sha256(const string &word) 
    {
        unsigned char *hash = SHA256((unsigned char*)word.c_str(), word.length(), NULL);
        char base64_hash[9];
        EVP_EncodeBlock((unsigned char*)base64_hash, hash, 6);
        return std::hash<string>{}(base64_hash) % 10;
    }

    /** Accessors */
    int *get_data()
    {
        return data;
    }
    int get_m()
    {
        return m;
    }
    int get_k()
    {
        return m;
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

    string dict = "./data/american-english";
    map<string, int> dictionary = parse_dict(dict);

    /*
    for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
        string str = it->first;
        vector<string> lines = split_line(str, 0);

        for (auto &line : lines)
            bf.insert(line);

        for (auto &line : lines)
            cout << bf.search(line) << "\n";

        cout << it->first << endl;
    }
    */

    bf.insert("hello");
    bf.insert("world");

    /* int *data = bf.get_data(); */
    /* for (int i = 0; i < bf.get_m(); i++) */
    /*     cout << data[i] << "\n"; */

    // "Might be in Bloom Filter with false positive probability 0.00675961"
    cout << bf.search("hello"); 
    // Not in Bloom Filter
    cout << bf.search("goodbye"); 
    return 0;
}

