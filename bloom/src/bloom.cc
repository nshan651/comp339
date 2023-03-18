#include <bloom.hh>
#include <hash.hh>
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
    }

    void insert(const string& element, const vector<lamb_hash> &hs)
    /** Insert hash into Bloom Filter. */
    {
        for (auto fun : hs) {
            size_t hash = fun(element, m) % m;
            data[hash] = 1;
        }
        n++;
    }

    string search(const string& element, const vector<lamb_hash> &hs)
    /** Search for a hash in the Bloom Filter. */
    {
        for (auto fun : hs) {
            size_t hash = fun(element, m) % m;
            if (data[hash] == 0)
                return "Not in Bloom Filter\n";
        }
        double prob = pow(1.0 - pow(1.0 - 1.0/m, k*n), k);
        return "Might be in Bloom Filter with false positive probability " + to_string(prob) + "\n";
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
    int get_n()
    {
        return n;
    }
    int get_k()
    {
        return k;
    }

    ~BloomFilter() 
    /** Destructor. */
    {
        delete[] data;
    }
};

int main(int argc, char **argv) 
{
    /* Define an array of hash functions to use */
    vector<lamb_hash> hashes;
    hashes.push_back(sha512);
    hashes.push_back(whirlpool);
    hashes.push_back(sha256);
    hashes.push_back(ripemd160);
    /* hashes.push_back(blake2); */

    int m = 0;
    int k = 0;

    CLI::App app("BloomFilter CLI");

    /* app.add_option("-m", m, "Number of bits")->required(); */
    app.add_option("-m", m, "Number of bits")->default_val(100);
    app.add_option("-k", k, "Number of hash functions")->default_val(2);

    CLI11_PARSE(app, argc, argv);

    /* Slice the list of available hash functions according to k */
    int end_slice = k < hashes.size() ? k : hashes.size();
    vector<lamb_hash> hs(hashes.begin(), hashes.begin() + end_slice);

    BloomFilter bf(m, k);

    string dict = "./data/american-english";
    /* string dict = "./data/hamlet.txt"; */
    ifstream infile(dict);
    string word;
    /* Insert all words in the dictionary */
    while (infile >> word) {
        bf.insert(word, hs);
    }
    infile.close();
    
    cout << bf.search("Hello", hs);
    cout << bf.search("No Way", hs); 
    cout << bf.search("ge", hs); 

    return 0;
}

