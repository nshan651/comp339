#include <lib.hh>
#include <CLI/CLI.hpp>


ifstream readFile(const string& fileName) {
    ifstream file(fileName);
    return file;
}

class BloomFilter 
{
    int m, k, n, collisions;
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
        this->collisions = 0;

        this->data = new int[m];
        memset(this->data, 0, m*sizeof(int));
        for (int i = 0; i < sizeof(data); i++)
            data[i] = 0;
    }

    /* void insert(const string &element, hash_func *hf) */
    void insert(const string& element, const vector<hash_func*> &hs)
    /** Insert hash into Bloom Filter. */
    {
        /* for (int i = 1; i <= k; i++) { */
        for (auto hf : hs) {
            int hash = (*hf)(element) % m;
            data[hash] = 1;
        }
        n++;
    }

    /* string search(const string &element, hash_func *hf) */
    string search(const string& element, const vector<hash_func*> &hs)
    /** Search for a hash in the Bloom Filter. */
    {
        /* vector<size_t> vhash; */
        vector<size_t> vhash;
        /* Collect hashes for k */
        /* for (int i = 0; i < k; i++) { */
        for (auto hf : hs) {
            /* size_t hash = hf[i](element) % m; */
            size_t hash = (*hf)(element) % m;
            vhash.push_back(hash);
        }
        /* Check if hashes in vhash are found in filter */
        for (size_t hash : vhash)
            if (data[hash] == 0)
                return "Not in Bloom Filter\n";
        
        double prob = pow((1.0 - pow((1.0 - 1.0/m), k*n)), k);
        double optimal_k = log(2) * m/n;
        /* cout << "Optimal k hashes " << optimal_k << endl; */
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
    int get_collisions()
    {
        return collisions;
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
    vector<hash_func*> hs;
    hs.push_back(hash_sha256());
    hs.push_back(hash_sha512());
    hs.push_back(hash_whirlpool());
    /* hs.push_back(hash_sha1); */

    int m = 0;
    int k = 0;

    CLI::App app("BloomFilter CLI");

    /* app.add_option("-m", m, "Number of bits")->required(); */
    app.add_option("-m", m, "Number of bits")->default_val(100);
    app.add_option("-k", k, "Number of hash functions")->default_val(2);

    CLI11_PARSE(app, argc, argv);

    BloomFilter bf(m, k);

    string dict = "./data/american-english";
    ifstream infile(dict); // open the file for input
    string word;

    cout << "Size: " << bf.get_n() << endl;

    /* Insert all words in the dictionary */
    while (infile >> word) {
        bf.insert(word, hs);
    }
    infile.close();

    string dict2 = "./data/american-english";
    ifstream infile2(dict2); // open the file for input
    string word2;
    /* Search each word for collisions */
    while (infile2 >> word2) {
        bf.search(word2, hs);
    }
    infile2.close();

    /* cout << bf.search("hello", hs); */
    /* bf.insert("hello", hs); */
    /* bf.insert("No way this is in it", hs); */
    /* bf.insert("world", hs); */
    // "Might be in Bloom Filter with false positive probability 0.00675961"
    /* cout << bf.search("hello", hs); */
    // Not in Bloom Filter
    /* cout << bf.search("goodbye", hs); */ 
    /* cout << bf.search("No way this is in it", hs); */ 
    return 0;
}

