#include <lib.hh>
#include <CLI/CLI.hpp>

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

    /* void insert(const string &element, hash_func *hf) */
    void insert(const string& element, const vector<hash_func*> &hs)
    /** Insert hash into Bloom Filter. */
    {
        /* for (int i = 1; i <= k; i++) { */
        for (auto hf : hs) {
            /* int hash = hash_sha256(element) % m; */
            /* int hash = hs[i](element) % m; */
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
    /* Define an array of hash functions to use */
    /* hash_func hash_functions[] = { */
    /*     hash_sha1, */
    /*     hash_sha256, */
    /*     hash_sha512, */
    /*     /1* hash_ripemd160, *1/ */
    /*     /1* hash_whirlpool *1/ */ 
    /* }; */
    vector<hash_func*> hs;
    hs.push_back(hash_sha256());
    hs.push_back(hash_sha256());
    /* hs.push_back(hash_sha1); */
    /* hs.push_back(hash_sha512); */

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

    bf.insert("hello", hs);
    bf.insert("world", hs);

    // "Might be in Bloom Filter with false positive probability 0.00675961"
    cout << bf.search("hello", hs);
    /* // Not in Bloom Filter */
    cout << bf.search("goodbye", hs); 
    cout << bf.search("No way this is in it", hs); 
    return 0;
}

